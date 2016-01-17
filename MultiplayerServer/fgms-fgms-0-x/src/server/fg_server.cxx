/**
 * @file fg_server.cxx
 */
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, U$
//

#define FGMS_USE_THREADS

//////////////////////////////////////////////////////////////////////
//
//      Server for FlightGear
//      (c) 2005-2012 Oliver Schroeder
//      and contributors (see AUTHORS)
//
//////////////////////////////////////////////////////////////////////
#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#ifndef _MSC_VER
	#ifndef __FreeBSD__
		#include <endian.h>
	#endif
	#include <sys/ipc.h>
	#include <sys/msg.h>
	#include <netinet/in.h>
#endif
#include <string>

#include "fg_cli.hxx"
#include "fg_server.hxx"    /* includes pthread.h */
#include "fg_common.hxx"
#include "fg_util.hxx"

#ifdef _MSC_VER
	#include <conio.h> // for _kbhit(), _getch
	typedef int pid_t;
#else
	cDaemon Myself;
#endif

bool    RunAsDaemon = false;
#ifndef DEF_SERVER_LOG
	#define DEF_SERVER_LOG "fg_server.log"
#endif

#ifndef DEF_UPDATE_SECS
	#define DEF_UPDATE_SECS 10
#endif

extern void SigHUPHandler ( int SigType );
#ifndef DEF_EXIT_FILE
	#define DEF_EXIT_FILE "fgms_exit"
#endif
#ifndef DEF_RESET_FILE
	#define DEF_RESET_FILE "fgms_reset"
#endif
#ifndef DEF_STAT_FILE
	#define DEF_STAT_FILE "fgms_stat"
#endif

#if _MSC_VER
	static char* exit_file   = ( char* ) DEF_EXIT_FILE; // "fgms_exit"
	static char* reset_file  = ( char* ) DEF_RESET_FILE; // "fgms_reset"
	static char* stat_file   = ( char* ) DEF_STAT_FILE; // "fgms_stat"
#else // !_MSC_VER
	static char* exit_file   = ( char* ) "/tmp/" DEF_EXIT_FILE;
	static char* reset_file  = ( char* ) "/tmp/" DEF_RESET_FILE;
	static char* stat_file   = ( char* ) "/tmp/" DEF_STAT_FILE;
#endif // _MSC_VER y/n

//////////////////////////////////////////////////////////////////////
/**
 * @class FG_SERVER
 */
/** @brief Constructor */
FG_SERVER::FG_SERVER
() : m_PlayerList("Users"),
	 m_DISbuffer ( DIS::BIG ),
	 m_2ndDISbuffer ( DIS::BIG )
{
	typedef union
	{
		uint32_t    complete;
		int16_t     High;
		int16_t     Low;
	} converter;
	m_Initialized		= false;// Init() will do it
	m_ReinitData		= true; // init the data port
	m_ReinitDIS			= true;	// init the DIS port
	m_ReinitDISEntityTable = true; // init the Entity Table
	m_fromFGPort		= 5000; // port for client connections
	m_Debug				= false;
	m_PlayerExpires		= 30; // standard expiration period
	m_Listening			= false;
	m_fromFGSocket		= 0;
	m_toFGSocket		= 0;
	m_DISSocket			= 0;
	m_DISPort			= 7000; //Default DIS-Port
	m_ProtocolVersion	= 6;//default DIS-Protocolversion
	m_ExerciseID		= 1; //default Exercise-ID
	m_PDUtype			= 1;//default PDU-Type
	m_myCallsign		= "FG";//default Callsign
	m_SmoothingTime		= 1.0;
	m_NumMaxClients		= 1;
	m_PlayerIsOutOfReach= 50;  // standard 100 nm
	m_ServerName		= "* Server *";
	m_BindAddress		= "";
	ConfigFile		= "";
	m_radarActive = false; //FG client uses specific radar based on the generic data in FGMP-Message
	m_shootCounter = 0; // number of used fire solutions
	m_emittingEventID	= 2;
	//m_stateUpdateIndicator = 1; // 1 means Changed Data Update
	
	// SetLog (SG_ALL, SG_DISABLED);
} // FG_SERVER::FG_SERVER()

//////////////////////////////////////////////////////////////////////
/**
 * @brief Standard destructor
 */
FG_SERVER::~FG_SERVER
()
{
	Done();
} // FG_SERVER::~FG_SERVER()

void*
receivePDU_helper
(
        void* context
)
{
	FG_SERVER* tmp_server = reinterpret_cast<FG_SERVER*> ( context );
	pthread_detach ( pthread_self() );
	tmp_server->receivePDU ( tmp_server );
	return 0;
}

void*
drLoop_helper
(
        void* context
)
{
	FG_SERVER* tmp_server = reinterpret_cast<FG_SERVER*> ( context );
	pthread_detach ( pthread_self() );
	tmp_server->internalDIS2FG_Loop ( tmp_server );
	return 0;
}

//////////////////////////////////////////////////////////////////////
/**
 * @brief Basic initialization
 *
 *  If we are already initialized, close
 *  all connections and re-init all variables
 */
int
FG_SERVER::Init
()
{
	//////////////////////////////////////////////////
	//      if we are already initialized, close
	//      all connections and re-init all
	//      variables
	//////////////////////////////////////////////////
	if ( m_Initialized == false )
	{
		if ( m_Listening )
		{
			Done();
		}
		m_Initialized       = true;
		m_Listening         = false;
		m_fromFGSocket      = 0;
		m_DISSocket			= 0;
		m_NumMaxClients     = 0;
		netInit (); // WinSocket initialisation
	}
	if ( m_ReinitData )
	{
		if ( m_fromFGSocket && m_toFGSocket)
		{
			delete m_fromFGSocket;
			m_fromFGSocket = 0;
			delete m_toFGSocket;
			m_toFGSocket = 0;
		}
		m_fromFGSocket = new netSocket();
		m_toFGSocket = new netSocket();
		if ( m_fromFGSocket->open ( false ) == 0 ) // UDP-Socket
		{
			SG_CONSOLE ( SG_FGMS, SG_ALERT, "FG_SERVER::Init() - "
			           << "failed to create listener socket" );
			return ( ERROR_CREATE_SOCKET );
		}
		m_fromFGSocket->setBlocking ( false );
		
		m_fromFGSocket->setSockOpt ( SO_REUSEADDR, true );
		
		if ( m_fromFGSocket->bind ( m_BindAddress.c_str(), m_fromFGPort ) != 0 )
		{
			SG_CONSOLE ( SG_FGMS, SG_ALERT, "FG_SERVER::Init() - "
			           << "failed to bind to port " << m_fromFGPort );
			SG_CONSOLE ( SG_FGMS, SG_ALERT, "already in use?" );
			return ( ERROR_COULDNT_BIND );
		}
		m_toFGSocket->open ( false );
		m_toFGSocket->setBlocking ( false );
		m_toFGSocket->setSockOpt ( SO_REUSEADDR, true );
		if (  m_toFGSocket->bind ( m_BindAddress.c_str(), m_DISPort ) != 0 )
		{
			SG_CONSOLE ( SG_FGMS, SG_ALERT, "FG_SERVER::Init() - "
			           << "failed to bind to port " << m_DISPort );
			SG_CONSOLE ( SG_FGMS, SG_ALERT, "already in use?" );
			return ( ERROR_COULDNT_BIND );
		}  
		m_ReinitData = false;
	}
	if ( m_ReinitDIS )
	{
		if ( m_DISSocket )
		{
			delete m_DISSocket;
			m_DISSocket = 0;
		}

		if ( m_DISPort != 0 )
		{
			m_DISSocket = new netSocket();
			m_DISAddress.set(m_DISBindAddress.c_str(), m_DISPort);

			if ( m_DISSocket->open ( false ) == 0 ) // UDP-Socket
			{
				SG_CONSOLE ( SG_FGMS, SG_ALERT, "FG_SERVER::Init() - "
						   << "failed to create DIS listener socket" );
				return ( ERROR_CREATE_SOCKET );
			}
			m_DISSocket->setBlocking ( false );
			m_DISSocket->setSockOpt ( SO_REUSEADDR, true );
			if ( m_DISSocket->bind ( m_BindAddress.c_str(), m_DISPort ) != 0 )
			{
				SG_CONSOLE ( SG_FGMS, SG_ALERT, "FG_SERVER::Init() - "<< "failed to bind to port " << m_DISPort );
				SG_CONSOLE ( SG_FGMS, SG_ALERT, "already in use?" );
				return ( ERROR_COULDNT_BIND );
			}
		}
		m_ReinitDIS = false;
	}
	if(m_ReinitDISEntityTable){

		// init table
		et.initializeEntityTable();
		m_ReinitDISEntityTable = false;
		}

	SG_CONSOLE (SG_FGMS, SG_ALERT, "# This is " << m_ServerName );
	SG_CONSOLE ( SG_FGMS, SG_ALERT, "# FlightGear Multiplayer Server v"
	           << VERSION << " started" );
	SG_CONSOLE ( SG_FGMS, SG_ALERT,"# listening to port " << m_fromFGPort );
	if ( m_DISSocket )
	{
		SG_CONSOLE ( SG_FGMS, SG_ALERT,"# DIS port " << m_DISPort );
	}
	else
	{
		SG_CONSOLE ( SG_FGMS, SG_ALERT,"# DIS port DISABLED");
	}
	if ( m_BindAddress != "" )
	{
		SG_CONSOLE ( SG_FGMS, SG_ALERT,"# listening on " << m_BindAddress );
	}
	FG_ListElement Entry("");
	SG_CONSOLE ( SG_FGMS, SG_ALERT, "# Files: exit=[" << exit_file << "] stat=[" << stat_file << "]" );
	m_Listening = true;
	return ( SUCCESS );
} // FG_SERVER::Init()

//////////////////////////////////////////////////////////////////////
/**
 * @brief Do anything necessary to (re-) init the server  used to handle kill -HUP
 */
void
FG_SERVER::PrepareInit
()
{
	// release all locks
	m_PlayerList.Unlock ();
} // FG_SERVER::PrepareInit ()

////////////////////////////////////////////////////////////////////////
///**
// * @brief Insert a new client to internal list
// * @param Sender
// * @param Msg
// */
void
FG_SERVER::AddClient
(
        const netAddress& Sender,
        char* Msg
)
{
	uint32_t	MsgMagic;
	string		Message;
	string		Origin;
	T_MsgHdr*	MsgHdr;
	T_PositionMsg*	PosMsg;
	FG_Player	NewPlayer;
	bool		IsLocal;
	MsgHdr		= ( T_MsgHdr* ) Msg;
	PosMsg		= ( T_PositionMsg* ) ( Msg + sizeof ( T_MsgHdr ) );
	MsgMagic	= XDR_decode<uint32_t> ( MsgHdr->Magic );
	IsLocal		= true;
	NewPlayer.Name	    = MsgHdr->Name;
	NewPlayer.Passwd    = "test"; //MsgHdr->Passwd;
	NewPlayer.ModelName = "* unknown *";
	NewPlayer.Origin    = Sender.getHost ();
	NewPlayer.Address   = Sender;
	NewPlayer.IsLocal   = IsLocal;
	NewPlayer.LastPos.Set (
	        XDR_decode64<double> ( PosMsg->position[X] ),
	        XDR_decode64<double> ( PosMsg->position[Y] ),
	        XDR_decode64<double> ( PosMsg->position[Z] )
	);
	NewPlayer.LastOrientation.Set (
	        XDR_decode<float> ( PosMsg->orientation[X] ),
	        XDR_decode<float> ( PosMsg->orientation[Y] ),
	        XDR_decode<float> ( PosMsg->orientation[Z] )
	);
	NewPlayer.ModelName = PosMsg->Model;
	m_PlayerList.Add ( NewPlayer, m_PlayerExpires );
	size_t NumClients = m_PlayerList.Size ();
	if ( NumClients > m_NumMaxClients )
	{
		m_NumMaxClients = NumClients;
	}
	Origin  = NewPlayer.Origin;
	if ( IsLocal )
	{
		Message = "New LOCAL Client: ";
	}
	else
	{
		Message = "New REMOTE Client: ";
	}
	SG_LOG ( SG_FGMS, SG_INFO, Message
	         << NewPlayer.Name << "@"
	         << Origin << ":" << Sender.getPort()
	         << " (" << NewPlayer.ModelName << ")"
	         << " current clients: "
	         << NumClients << " max: " << m_NumMaxClients
	       );
} // FG_SERVER::AddClient()

//////////////////////////////////////////////////////////////////////
/**
 * @brief Handle client connections
 * @param Msg
 * @param Bytes
 * @param SenderAddress
 * local FG-Multiplayermessages dont get send, we just do the translation to DIS and send DIS packets!
 */
void
FG_SERVER::ReceiveFGPacket
(
        char* Msg,
        int   Bytes,
        const netAddress& SenderAddress,
		unsigned int currentTime,
		unsigned int* nextHeartBeat 
)
{
	T_MsgHdr*       MsgHdr;
	T_PositionMsg*  PosMsg;
	uint32_t        MsgId;
	uint32_t        MsgMagic;
	Point3D         SenderPosition;
	PlayerIt	CurrentPlayer;
	MsgHdr    = ( T_MsgHdr* ) Msg;
	MsgMagic  = XDR_decode<uint32_t> ( MsgHdr->Magic );
	MsgId     = XDR_decode<uint32_t> ( MsgHdr->MsgId );
	MSG2ndPart*		msg2ndpart;
	unsigned int	elapsedTime = 0; //age of esPDU (difference from pdu timestamp to current time) in ms
	double			elapsedTimeDBL = 0; //typecasted elpsed time in seconds, floattype necessary for not losing precision
	int				HBT_ESPDU = 5000; //HeartBeatTime for ES-PDU in ms
	double			devOrient; //Deviation between internal (true) und external (deadreckoned) Orientation
	double			DRA_ORIENT_THRSH = 3.0; //DeadReckoningAlgorithm Orientation Threshold in °
	double			devPos; //Deviation between internal (true) und external (deadreckoned) Position
	double			DRA_POS_THRSH = 1.0; //DeadReckoningAlgorithm Position Threshold in m
	bool			sendESPDU = false; //Flag for sending Entity State PDU, true if any threshold (time, position, orientation) is reached, else false
	bool			sendFirePDU = false; //Flag for sending Fire PDU, true if Chat string in Multiplayer Message contains Fire solution
	DIS::EntityStatePdu	TargetESPDU; // last esPDU of target for FirePDU
	DIS::EntityType MunitionType; // MunitionType for FirePDU
	bool			sendEEPDU = false; //Flag for sending Entity State PDU, true if ...

	/////////////////////////////////////////////////
	//
	//    Add Client to list if its not known
	//
	//////////////////////////////////////////////////
	m_PlayerList.Lock();
	CurrentPlayer = m_PlayerList.FindByName ( MsgHdr->Name );
	
	if (CurrentPlayer == m_PlayerList.End () )
	{
		m_PlayerList.Unlock();
		// unknown, add to the list
		if ( MsgId != POS_DATA_ID )
		{
			// ignore clients until we have a valid position
			return;
		}
		if (MsgHdr->ReplyAddress == 0)
		{
			std::cout << std::endl;
			std::cout << "Added " << MsgHdr->Name << " to Playerlist" << std::endl;
			AddClient ( SenderAddress, Msg );
		}
	}
	else
	{
		m_PlayerList.Unlock();
	}
	
	//////////////////////////////////////////////////
	//
	//    translate and send DIS packet
	//
	//////////////////////////////////////////////////
	if ( MsgId == POS_DATA_ID && MsgHdr->Name == m_myCallsign )
	{
		PosMsg = ( T_PositionMsg* ) ( Msg + sizeof ( T_MsgHdr ) );
		double x = XDR_decode64<double> ( PosMsg->position[X] );
		double y = XDR_decode64<double> ( PosMsg->position[Y] );
		double z = XDR_decode64<double> ( PosMsg->position[Z] );
		if ( ( x == 0.0 ) || ( y == 0.0 ) || ( z == 0.0 ) )
		{
			// ignore while position is not settled
			return;
		}
		
		try
		{
			//find DIS EntityType in EntityTabl
			DIS::EntityType* entityType = et.getDISModelFromFGModel(PosMsg->Model);
			//check if FG-model is mapped to an DIS-entitytype in the entitytable
			if(entityType != NULL)
				{
				//create ESPDU
				DIS::EntityStatePdu esPDU4dr; //is initialitzed with all zeroes
				DIS::EntityStatePdu esPDU;
				esPDU = DISBroker::createESPDU( MsgHdr, PosMsg, m_forceID );
				esPDU4dr = FG_Client[m_myCallsign]; //for very first FGpacket no client exists, so values in esPDU4dr stay zero, for all other FGpackages client contains last received PDU
				//how old is the PDU?
				unsigned int oldTimeStamp = esPDU4dr.getTimestamp()/2/pow(2.0, 31)*3600000;
				elapsedTime = currentTime - oldTimeStamp;
				//std::cout << "Delta T: " << elapsedTime << " ms\n";
				elapsedTimeDBL =  (double)(elapsedTime)/1000;			

				if(currentTime >= *nextHeartBeat) //DIS-Heartbeat of 5 seconds is over, due to startvalue of nextDISHeartbeat of -1 this statement is true for very first received MP-Message
				{
					sendESPDU = true;
					//m_stateUpdateIndicator = 0; // 0 means Heartbeat Update
					//std::cout << "HeartBeat reached: " << currentTime - *nextHeartBeat + 5000 << " ms\n";
				}
				else //No Time for DIS-HeartBeat, but some Thresholds may be reached
				{
					//do dead reckoning for FG-Client
					dr::calcDR( &esPDU4dr, elapsedTimeDBL );
					double devX = (esPDU4dr.getEntityLocation().getX() - esPDU.getEntityLocation().getX());
					double devY = (esPDU4dr.getEntityLocation().getY() - esPDU.getEntityLocation().getY());
					double devZ = (esPDU4dr.getEntityLocation().getZ() - esPDU.getEntityLocation().getZ());
					devPos  = pow(devX*devX + devY*devY + devZ*devZ, 0.5);
					if(devPos > 1.0) //Threshold for Position reached (this is always true for very first package due to zeros in esPDU4dr)
					{
						sendESPDU = true;
						//std::cout << "PositionTHRSH reached: " << devPos << " m\n";
					}
					else
					{
						devOrient  = (esPDU4dr.getEntityOrientation().getPhi()   - esPDU.getEntityOrientation().getPhi())  *(esPDU4dr.getEntityOrientation().getPhi()   - esPDU.getEntityOrientation().getPhi());
						devOrient += (esPDU4dr.getEntityOrientation().getPsi()   - esPDU.getEntityOrientation().getPsi())  *(esPDU4dr.getEntityOrientation().getPsi()   - esPDU.getEntityOrientation().getPsi());
						devOrient += (esPDU4dr.getEntityOrientation().getTheta() - esPDU.getEntityOrientation().getTheta())*(esPDU4dr.getEntityOrientation().getTheta() - esPDU.getEntityOrientation().getTheta());
						devOrient  = pow(devOrient, 0.5);
						if(devOrient > 3.0)
						{
							sendESPDU = true;
							//std::cout << "OrientTHRSH reached: " << devOrient << "°\n";
						}
					}
				}
				if(m_radarActive == true)
				{
					//unpack second data part of FGMP-Message
					msg2ndpart = new MSG2ndPart(Msg,Bytes);
					//check for and read fire solution
					if(msg2ndpart->getFireSolution(TargetESPDU, MunitionType, m_shootCounter, disMap, et))
					{
						sendFirePDU = true;
					}
					//decide for sendEEPDU
					//rules are similiar to those of the platform, since radar is fised to platform ESPDU and EEPDU can be send together
					sendEEPDU = sendESPDU;
				}
				if(sendESPDU == true)
				{
					//set EntityID 
					esPDU.getEntityID().setSite(m_DISSite);
					esPDU.getEntityID().setApplication(m_DISApplication);
					esPDU.getEntityID().setEntity(1);
					//set DIS EntityType
					esPDU.setEntityType(*entityType);
					/*testweise direkt hier senden*/
					//compute DIS Timestamp only use 31 bit of 32bit integer
					double timestamp = pow(2.0, 31) * (double)currentTime / 3600000;
					//last bit has to be 0 for absolute timestamp, thus do bitshift (simply multiply with 2)
					//TODO case statement for switching between absolute and relative timestamp (relative = absolute + 1, so that last bit is always 1)
					unsigned int DISTimeStamp = (unsigned int)timestamp * 2; ;
					esPDU.setTimestamp( DISTimeStamp );
					//serialize for network sending
					esPDU.marshal( m_DISbuffer );
					//send PDU
					m_DISSocket->sendto( &m_DISbuffer[0], m_DISbuffer.size(), 0, &m_DISAddress );
					FG_Client.Lock();
					//put it in DISMap
					FG_Client [MsgHdr->Name] = esPDU;
					FG_Client.Unlock();
					//clear betwork buffer
					m_DISbuffer.clear();
					/*testweise senden Ende*/
					*nextHeartBeat = currentTime + HBT_ESPDU - m_DIS2FGUpdaterate /*Timesframe of FG2DIS-Messages in ms*/;
				}

				if(sendFirePDU == true)
				{
					//create FPDU
					DIS::FirePdu fPDU = DISBroker::createFPDU(esPDU4dr,TargetESPDU, MunitionType, m_shootCounter, currentTime);
					//serialize for network sending
					fPDU.marshal(m_DISbuffer);
					//send PDU
					m_DISSocket->sendto( &m_DISbuffer[0], m_DISbuffer.size(), 0, &m_DISAddress );
					//clear betwork buffer
					m_DISbuffer.clear();
				}
				if(sendEEPDU == true)
				{
					//create FPDU
					DIS::ElectronicEmissionsPdu eePDU = DISBroker::createEEPDU(esPDU, m_emittingEventID, currentTime);
					//serialize for network sending
					eePDU.marshal(m_DISbuffer);
					//send PDU
					m_DISSocket->sendto( &m_DISbuffer[0], m_DISbuffer.size(), 0, &m_DISAddress );
					//clear betwork buffer
					m_DISbuffer.clear();
				}
			}//endif entity exists in entitytable
			else
			{
				std::cout << "can not process FG-Message: " << PosMsg->Model << " does not exist in entitytable.xml\n";
			}

		}
		catch (int e)
		{
			cout << " An Exception occurred in Sending DIS-Packet. Exception Nr. " << e << endl;
		}
	}
} // FG_SERVER::HandlePacket ();



//////////////////////////////////////////////////////////////////////
/**
 * @brief Handle DIS client connections to FG Clients
 * @param Msg
 * @param Bytes
 * @param SenderAddress
 */
void
FG_SERVER::SendMPMessage
(
        char* Msg,
        int   Bytes		
)
{
	T_MsgHdr*       MsgHdr;
	T_PositionMsg*  PosMsg;
	uint32_t        MsgId;
	Point3D         PlayerPosGeod;
	PlayerIt		CurrentPlayer;
	FG_Player		SendingPlayer;
	unsigned int    PktsForwarded = 0;
	MsgHdr    = ( T_MsgHdr* ) Msg;
	MsgId     = XDR_decode<uint32_t> ( MsgHdr->MsgId );


	//////////////////////////////////////////////////
	//
	//      send the packet to all FG clients.
	//
	//////////////////////////////////////////////////
	MsgHdr->Magic = XDR_encode<uint32_t> ( MSG_MAGIC );
	
	CurrentPlayer = m_PlayerList.Begin();

	while ( CurrentPlayer != m_PlayerList.End() )
	{

		//////////////////////////////////////////////////
		//
		//  only send packet to local clients
		//	should not be necessary, but do it just to be sure
		//
		//////////////////////////////////////////////////
		if ( CurrentPlayer->IsLocal )
		{
			PosMsg = ( T_PositionMsg* ) ( Msg + sizeof ( T_MsgHdr ) );
			m_toFGSocket->sendto ( Msg, Bytes, 0, &CurrentPlayer->Address );
			//std::cout << "Lag: " << XDR_decode64<double>(PosMsg->lag) << std::endl;
			//std::cout << "Time: " << XDR_decode64<double>(PosMsg->time) << std::endl;

			if(m_Debug){
			std::cout << "DIS to MSG Send" << std::endl;
			std::cout << MsgHdr->Name << " send to: " << CurrentPlayer->Name << std::endl;
			std::cout << "Send to: " << CurrentPlayer->Origin << ":" << CurrentPlayer->Address.getPort() << std::endl;
			std::cout << "Using Model: " << PosMsg->Model << std::endl;
			std::cout << "Pos X: " << XDR_encode64<double>(PosMsg->position[X]) << std::endl;
			std::cout << "Ori X: " << XDR_decode<float>(PosMsg->orientation[X]) << std::endl;
			std::cout << "angularAccel X: " << XDR_decode<float>(PosMsg->angularAccel[X]) << std::endl;
			std::cout << "angularVel X: " << XDR_decode<float>(PosMsg->angularVel[X]) << std::endl;
			std::cout << "linearAccel X: " << XDR_decode<float>(PosMsg->linearAccel[X]) << std::endl;
			std::cout << "linearVel X: " << XDR_decode<float>(PosMsg->linearVel[X]) << std::endl;
			std::cout << "Lag: " << PosMsg->lag << std::endl;
			std::cout << "----------------------------------------" << std::endl;
				}
			
			m_PlayerList.UpdateSent (CurrentPlayer, Bytes);
			PktsForwarded++;
		}//endif ( CurrentPlayer->IsLocal )
		CurrentPlayer++;
		
	}//while

} // FG_SERVER::HandleDISPacket ();


//////////////////////////////////////////////////////////////////////
/**
 * @brief Main loop of the server
 */
int
FG_SERVER::incomingMessageEvent_Loop
()
{
	int         Bytes;
	char        Msg[MAX_PACKET_SIZE];
	netAddress  SenderAddress;
	netAddress  DRAddress;
	netSocket*  ListenSockets[2+1];//Lstening for DIS-PDUs and for FGMP-Messages, third Pointer is Zero-Pointer for loop-termination in netsocket->select
	//Socket for receiving DIS PDUs
	DIS::EntityStatePdu esPDU4dr; //PDU for deadreckoning
	unsigned int currentTime;
	unsigned int nextDISHeartBeat = -1; //Time for next DIS-HeartBeat, presetvalue necessary for processing first MP-Message without doing dead reckoning
	time_t		CurrentTime;

	//get system time
	computeMilliSecHour( &currentTime );
	if ( m_Listening == false )
	{
		SG_LOG ( SG_FGMS, SG_ALERT, "FG_SERVER::Loop() - "
		           << "not listening on any socket!" );
		return ( ERROR_NOT_LISTENING );
	}
#ifdef _MSC_VER
	SG_LOG ( SG_FGMS, SG_ALERT,  "ESC key to EXIT (after select " << m_PlayerExpires << " sec timeout)." );
#endif

	//try to open socket
	if ( m_DISSocket->open ( false ) == 0 ) // UDP-Socket
	{
		SG_CONSOLE ( SG_FGMS, SG_ALERT, "FG_SERVER::Init() - "
					<< "failed to create DIS listener socket" );
		int errorCode = 2;//integer for return value
		return ( errorCode );//must be pointer (void* defined in pthread)
	}
	//configure socket
	m_DISSocket->setBlocking ( false );
	m_DISSocket->setSockOpt ( SO_REUSEADDR, true );
	//bind socket
	if ( m_DISSocket->bind ( "broadcast", m_DISPort ) != 0 )
	{
		std::cout << "failed to bind disSocket" <<  std::endl ;
		SG_CONSOLE ( SG_FGMS, SG_ALERT, "already in use?" );
		int errorCode = 3;//integer for return value
		return ( errorCode );//must be pointer (void* defined in pthread)
	}

	//create thread for Dead Reckoning
	pthread_t drThread;
	pthread_create ( &drThread, NULL, drLoop_helper, this );

	//////////////////////////////////////////////////
	//
	//      infinite listening loop
	//
	//////////////////////////////////////////////////
	while ( true )
	{
		////create thread for listening for DIS-Packets
		//pthread_t disThread;
		//pthread_create ( &disThread, NULL, receivePDU_helper, this );
		if ( m_DISSocket > 0 )// DIS Socket
		{
			receivePDU(this);
		}//endif ( m_DISSocket > 0 ) DIS Socket

		if (! m_Listening )
		{
			cout << "bummer 1!" << endl;
			return 1;
		}
		if (m_fromFGSocket == 0)
		{
			cout << "bummer 2!" << endl;
			return 2;
		}
		if (m_DISSocket == 0)
		{
			cout << "bummer 3!" << endl;
			return 3;
		}
		try
			{
			//get system time in  milliseconds past full hour
			computeMilliSecHour( &currentTime );
			//get time in seconds
			CurrentTime	= time (0);
			}
		catch (int e)
			{
			cout << " An Exception occurred while getting systime. Exception Nr. " << e << endl;
			}

		errno = 0;
		ListenSockets[0] = m_fromFGSocket;
		ListenSockets[1] = m_DISSocket;
		ListenSockets[2] = NULL;
		Bytes = m_fromFGSocket->select ( ListenSockets, ListenSockets, 0 );
		if ( Bytes < 0 )
		{	// error
			continue;
		}
		

		if ( ListenSockets[0] > 0 )// DataSocket
		{
			// something on the wire (clients)
			Bytes = m_fromFGSocket->recvfrom ( Msg,MAX_PACKET_SIZE, 0, &SenderAddress );
			if ( Bytes <= 0 )
			{
				continue;
			}
			ReceiveFGPacket ( ( char* ) &Msg, Bytes, SenderAddress, currentTime, &nextDISHeartBeat );
		} // DataSocket

		memset(&Msg[0], 0, sizeof(Msg));
	}

	return ( 0 );
} // FG_SERVER::Loop()

//////////////////////////////////////////////////////////////////////
/**
 * @brief  Set listening port for incoming clients
 */
void
FG_SERVER::SetFromFGPort
(
        int Port
)
{
	if ( Port != m_fromFGPort )
	{
		m_fromFGPort = Port;		m_ReinitData   = true;
	}
} // FG_SERVER::SetPort ( unsigned int iPort )


//////////////////////////////////////////////////////////////////////
/**
 * @brief Set listening port for DIS
 */
void
FG_SERVER::SetDISPort
(
        int Port
)
{
	if ( m_DISPort != Port )
	{
		m_DISPort = Port;
		m_ReinitDIS = true;
	}
} // FG_SERVER::SetDISPort ( unsigned int iPort )

//////////////////////////////////////////////////////////////////////
/**
 * @brief Set DIS Site
 */
void
FG_SERVER::SetDISSite 
(
        int Site
)
{
	if ( m_DISSite != Site )
	{
		m_DISSite = Site;
	}
} // FG_SERVER::SetDISSite ( unsigned int Site )

//////////////////////////////////////////////////////////////////////
/**
 * @brief Set DIS Application
 */
void
FG_SERVER::SetDISAppl 
(
        int Application
)
{
	if ( m_DISApplication != Application )
	{
		m_DISApplication = Application;
	}
} // FG_SERVER::SetDISApplication ( unsigned int Application )

//////////////////////////////////////////////////////////////////////
/**
 * @brief Set DIS ForceID
 */
void
FG_SERVER::SetForceID 
(
        int forceID
)
{
	if ( m_forceID != forceID )
	{
		m_forceID = forceID;
	}
} // FG_SERVER::SetDISApplication ( unsigned int Application )

 //////////////////////////////////////////////////////////////////////
/**
 * @brief Set DIS FGUpdaterate (time in ms)
 */
void
FG_SERVER::SetDIS2FGUpdaterate 
(
        double FGUpdate
)
{

	m_DIS2FGUpdaterate = ( 1 / FGUpdate ) * 1000;
	
} // FG_SERVER::SetDIS2FGUpdaterate ( double FGUpdaterate )

 //////////////////////////////////////////////////////////////////////
/**
 * @brief Set Callsign for our local FG-Client
 */
void
FG_SERVER::SetMyCallsign
(
        string callsign
)
{

	m_myCallsign = callsign;
	
} // FG_SERVER::SetMyCallsign ( string callsign )

//////////////////////////////////////////////////////////////////////
/**
 * @brief Set time in seconds. if no packet arrives from a client
 *        within this time, the connection is dropped.
 */
void
FG_SERVER::SetPlayerExpires
(
        int Seconds
)
{
	m_PlayerExpires = Seconds;
} // FG_SERVER::SetPlayerExpires ( int iSeconds )
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/**
 * @brief Set nautical miles two players must be apart to be out of reach
 */
void
FG_SERVER::SetOutOfReach
(
        int OutOfReach
)
{
	m_PlayerIsOutOfReach = OutOfReach;
} // FG_SERVER::SetOutOfReach ( int iOutOfReach )
//////////////////////////////////////////////////////////////////////

void  
FG_SERVER::SetRadarActive ( bool activeRadar )
{
	m_radarActive = activeRadar;
}

//////////////////////////////////////////////////////////////////////
/**
 * @brief  Set the server name
 */
void
FG_SERVER::SetServerName
(
        const std::string& ServerName
)
{
	m_ServerName = ServerName;
} // FG_SERVER::SetServerName ( const std::string &ServerName )
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/**
 * @brief Set the address this server listens on
 */
void
FG_SERVER::SetBindAddress
(
        const std::string& BindAddress
)
{
	m_BindAddress = BindAddress;
} // FG_SERVER::SetBindAddress ( const std::string &BindAddress )
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/**
 * @brief Set the address for the DIS broadcast
 */
void
FG_SERVER::SetDISAddress
(
        const std::string& DISAddress
)
{
	//m_DISAddress.set(m_DISBindAddress.c_str(), m_DISPort);
	m_DISBindAddress = DISAddress;
} // FG_SERVER::SetDISAddress ( const std::string &DISAddress )
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/**
 * @brief  Close sockets, logfile etc.
 */
void
FG_SERVER::Done
()
{
	SG_LOG ( SG_FGMS, SG_ALERT, "FG_SERVER::Done() - exiting" );
	if ( m_Listening == false )
	{
		return;
	}
	if ( m_fromFGSocket )
	{
		m_fromFGSocket->close();
		delete m_fromFGSocket;
		m_fromFGSocket = 0;
	}
	if ( m_DISSocket )
	{
		m_DISSocket->close();
		delete m_DISSocket;
		m_DISSocket = 0;
		m_DISbuffer.~DataStream();
		m_2ndDISbuffer.~DataStream();
	}
	m_PlayerList.Unlock ();		m_PlayerList.Clear ();
	disMap.Clear (); 
	disMapSmooth.Clear();
	FG_Client.Clear();
	m_Listening = false;
} // FG_SERVER::Done()


//////////////////////////////////////////////////////////////////////
/**
 * @brief Decide whether the relay is interested in full rate updates.
 * @see \ref server_out_of_reach config.
 * @param Relay
 * @param SendingPlayer
 * @retval true is within range
 */
bool
FG_SERVER::IsInRange
(
        FG_ListElement& Relay,
        FG_Player& SendingPlayer
)
{
	FG_Player CurrentPlayer;
	size_t	 Cnt;
	Cnt = m_PlayerList.Size ();
	for (size_t i = 0; i < Cnt; i++)
	{
		CurrentPlayer = m_PlayerList[i];
		if (CurrentPlayer.ID == FG_ListElement::NONE_EXISTANT)
			continue;
		if ( ( CurrentPlayer.Address == Relay.Address )
		&& ( Distance ( SendingPlayer.LastPos, CurrentPlayer.LastPos ) <= m_PlayerIsOutOfReach ) )
		{
			return true;
		}
	}
	return false;
} // FG_SERVER::IsInRange()
//////////////////////////////////////////////////////////////////////

string FG_SERVER::ToString(unsigned short wert){
	int zahl;
	ostringstream Str;
	zahl = wert;
	Str << zahl;
	string super(Str.str());
	return super;
	}

//add new entry(DIS EntityStatePDU) to DeadReckoning Buffer
string FG_SERVER::addToDISMap(DIS::EntityStatePdu * esPDU)
	{
	std::string key;
	try
	{
		unsigned int currentTime;
		//get system time
		computeMilliSecHour ( &currentTime );
		key = CallSignManager::getCallSign( esPDU->getEntityID().getSite(), esPDU->getEntityID().getApplication(), esPDU->getEntityID().getEntity() );

		if (key != "IMWRONG" )
		{
			//set timestamp
			esPDU->setTimestamp(currentTime);
			//ad to DISMap
			disMap.Lock();
			disMap[key] = *esPDU;
			disMap.Unlock();
		}//endif (key != "IMWRONG" )

	}//try
	catch (int e)
		{
		cout << " An Exception occurred addToDRBuffer. Exception Nr. " << e << endl;
		}
	return key;

	}

//////////////////////////////////////////////////////////////////////
/**
 * @receives and processes ESPDUs
 */
void* FG_SERVER::receivePDU (void * This)
{
	FG_SERVER* serverPtr = (FG_SERVER *)This;//Pointer to Server-Objekt
	int				Bytes;
	char			Msg[FG_SERVER::MAX_PACKET_SIZE];
	unsigned char	tmpChar;
	netAddress		SenderAddress;
	netAddress		DRAddress;
	DIS::EntityStatePdu esPDU;
	DIS::DataStream	disBuffer( DIS::BIG );
	DIS::DataStream	secondDISbuffer( DIS::BIG );
	double			deltaSendTime = 0;

	
	// something on the wire (DIS port)
	//std::cout << "Daten sind da \n";
	Bytes = serverPtr->m_DISSocket->recvfrom ( Msg, MAX_PACKET_SIZE, 0, &SenderAddress );
			
	if ( Bytes <= 0 )
	{
		return NULL;
	}
	try
		{
		//std::cout << Bytes << std::endl;
		disBuffer.SetStream( Msg, sizeof(Msg), DIS::BIG);
		secondDISbuffer = disBuffer;

		//unmarshal Protocolversion
		secondDISbuffer >> tmpChar;
		if ( unsigned short (tmpChar) != serverPtr->m_ProtocolVersion )
			{	//if Protocolversion does not match, clear the buffers and exit if-statement
				disBuffer.clear();
				secondDISbuffer.clear();
				return NULL;
			}
		//unmarshal ExerciseID
		secondDISbuffer >> tmpChar;
		if ( unsigned short ( tmpChar) != serverPtr->m_ExerciseID )
			{	//if ExerciseID does not match, clear the buffers and exit if-statement
				disBuffer.clear();
				secondDISbuffer.clear();
				return NULL;
			}
		//unmarshal PDU-Type
		secondDISbuffer >> tmpChar;		
		//printf ("PDU-Type: %u \n" , tmpChar );
		//check if it is a EntityStatePDU
		if ( unsigned short (tmpChar) == 1  )
		{
			//std::cout << "Ist ESPDU \n";
			//code for converting ES-PDU to fg-messages
			esPDU.unmarshal(disBuffer);
			//check if PDU is from us (prevents from receiving our own DIS-broadcst)
			if (esPDU.getEntityID().getSite() != serverPtr ->m_DISSite && esPDU.getEntityID().getApplication() != serverPtr->m_DISApplication )
			{
				//std::cout << "nicht von mir \n";
				//lock the DISMap
				serverPtr->FG_Client.Lock();
				//check if there is a local FG client
				//if we dont have a local FG client, we dont need to process DIS-PDUs
				if (serverPtr->FG_Client.find ( serverPtr ->m_myCallsign ) != serverPtr->FG_Client.end() )
				{
					//std::cout << "ich bin da \n";
					//local copy of the last PDU from our own FG-Client

					DIS::EntityStatePdu myPDU = serverPtr->FG_Client[ serverPtr ->m_myCallsign ];
					//unlock the map, because now we got our local copy
					serverPtr->FG_Client.Unlock();
					//check distance between us and received entity
					double xPosDiff = esPDU.getEntityLocation().getX() - myPDU.getEntityLocation().getX() ;
					double yPosDiff = esPDU.getEntityLocation().getY() - myPDU.getEntityLocation().getY() ;
					double zPosDiff = esPDU.getEntityLocation().getZ() - myPDU.getEntityLocation().getZ() ;
					double posDiff =  xPosDiff*xPosDiff + yPosDiff*yPosDiff + zPosDiff*zPosDiff;
					posDiff = pow(posDiff, 0.5);
					//std::cout << std::endl << "posDiff: " << posDiff/1852 << std::endl << std::endl;

					//only if distance is smaller than m_PlayerIsOutOfReach(config-file) do the processing
					if ( posDiff/1852 <= serverPtr->m_PlayerIsOutOfReach )
					{

						//to be safe clear ArticulatedParameters (sometimes creepy stuff is in there)
						esPDU.getArticulationParameters().clear();
						//put PDU in disMap
						serverPtr->addToDISMap( &esPDU );
					}//endif ( posDiff/1852 <= serverPtr ->m_PlayerIsOutOfReach )
						
				}//endif (serverPtr->disMap[serverPtr->m_myCallsign] != serverPtr->disMap.End() )
				else
				{
					//Unlock DISMap
					serverPtr -> FG_Client.Unlock();
				}

			}//endif (esPDU.getEntityID().getSite() != site  )

		}//endif ( unsigned short (tmpChar) == 1  )
		//clear the buffers
		disBuffer.clear();
		secondDISbuffer.clear();
		}//try
	catch  (int e)
		{
		cout << " An Exception occurred in DIS-Socket. Exception Nr. " << e << endl;
		}//catch

	//clear message
	memset(&Msg[0], 0, sizeof(Msg));


	return NULL;
}//FG_SERVER::receivePDU(void *arg)
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/**
 * @brief starts infinite listening loop for Dead Reckoning
 */
void* FG_SERVER::internalDIS2FG_Loop (void * This)
{
	FG_SERVER*		serverPtr = (FG_SERVER *)This;//Pointer to Server-Objekt
	char			Msg[FG_SERVER::MAX_PACKET_SIZE];
	DIS::EntityStatePdu sendPDU;
	DIS::EntityStatePdu drPDU;
	DIS::EntityStatePdu mySmoothPDU;
	unsigned int	currentTime = 0; //current system time for each mp-contact in iteration loop in ms
	unsigned int	startTime = 0; //start time for iteration through alls mp-contacts in ms
	unsigned int    elapsedTime = 0; //age of esPDU (difference from pdu timestamp to current time) in ms
	double			elapsedTimeDBL = 0; //typecasted elpsed time in seconds, floattype necessary for not losing precision
	bool			abort =	false;
	std::string		model;
	std::string		callSign;
	std::map<std::string, DIS::EntityStatePdu> lastUpdateMap;
	std::map<std::string, DIS::EntityStatePdu> smoothingMap;
	//put some server-values in local variables, because there ae used so often
	std::string		mycallSign	= serverPtr ->m_myCallsign;
	double			fgUpdaterate= serverPtr ->m_DIS2FGUpdaterate;
	int				timeOut		= serverPtr ->m_PlayerExpires * 1000;
	//variables for smoothing algorithm
	double			smoothingTime = serverPtr ->m_SmoothingTime; //delay constant of first order filter
	double			timeStep = 1/(smoothingTime/((double)fgUpdaterate/1000)); //first (=1) timestep (comparable to i/n for i=1 in IEEE1278.2 smoother)
	//int				sendedTracks = 0;

	//infenite working loop
	while ( abort == false)
	{
		//compute start tim for this loop
		computeMilliSecHour ( &startTime ); 
		try
		{
			//lock disMap
			serverPtr ->disMap.Lock();
			//iterator for disMap
			std::map<string, DIS::EntityStatePdu>::iterator i = serverPtr ->disMap.begin();
			//iterate trough disMap
			while(i != serverPtr ->disMap.end())
			{

				//callSign for FG-message
				callSign = i->first;
				//compute current time
				computeMilliSecHour( &currentTime );
				//how old is the PDU?
				elapsedTime = currentTime - i->second.getTimestamp();
				//unlock disMap
				serverPtr ->disMap.Unlock();

				//if PDU is to old delete it from disMap
				if ( elapsedTime > timeOut )
				{
					//Lock disMap
					serverPtr ->disMap.Lock();
					std::cout << "Entity "<< i->second.getEntityID().getSite() << ":" << i->second.getEntityID().getApplication() << ":" << i->second.getEntityID().getEntity() << " dropped" << std::endl;
					//erase entry
					serverPtr ->disMapSmooth.erase(callSign);
					serverPtr ->disMap.erase( i++ );
				}
				//if PDU is not too old
				else 
				{
					//check if Entity exists in Filter
					if (serverPtr ->disMapSmooth.find(callSign) != serverPtr->disMapSmooth.end())
					{
						//local copy of the PDU
						drPDU = i->second;
						mySmoothPDU = serverPtr->disMapSmooth[callSign];
						elapsedTimeDBL =  (double)(elapsedTime)/1000;
						//prognosting the future (now + smoothingTime) position of the entity based on dead reckoning
						dr::calcDR( &drPDU, elapsedTimeDBL + smoothingTime );
						//smooth pdu
						smoothPDU(&drPDU, &mySmoothPDU, timeStep);
						//write local copy back to map and send smoothed copy
						serverPtr->disMapSmooth[callSign] = mySmoothPDU;
						sendPDU = mySmoothPDU;
					}
					else
					{//Entity is new
						sendPDU = i->second;
						serverPtr->disMapSmooth[callSign] = sendPDU;
					}
					//generate model for FG-message
					model = serverPtr ->et.getFGModel( sendPDU.getEntityType() );
					sendPDU.setTimestamp( currentTime );
					// create MPMessage from DIS_PDU
					DISBroker::createMPmessage( Msg, sendPDU, model, callSign, MAX_PACKET_SIZE, &fgUpdaterate, serverPtr->et, serverPtr->m_forceID);	
					//send FG-Multiplayermessage
					serverPtr ->SendMPMessage( Msg, sizeof(Msg) );	// DIS-Track als FG-MP-Message an FlightGear Client versenden
					//zero the message
					memset(&Msg[0], 0, sizeof(Msg));
					//unlock disMap
					serverPtr ->disMap.Lock();
					i++;
					//sendedTracks++;
				}
			}//while( i != serverPtr ->disMap.end() )

			//unlock disMap
			serverPtr ->disMap.Unlock();
			//zero the message
			memset(&Msg[0], 0, sizeof(Msg));
								
		}//try
		catch  (int e)
		{
			cout << " An Exception occurred in DR-Loop. Exception Nr. " << e << endl;
			abort = true;
		}//catch

		//compute current Time
		computeMilliSecHour ( &currentTime );

		memset(&Msg[0], 0, sizeof(Msg));

		if ((currentTime - startTime) < fgUpdaterate)
		{
			Sleep (fgUpdaterate - (currentTime - startTime));			//only sleep if elapsed time is smaller than updaterate
		}
		//sendedTracks = 0;
	}//while( abort == false)

	
	return NULL;
}//FG_SERVER::drLoop(void *arg)

//////////////////////////////////////////////////////////////////////
/**
 * @brief smoothes DIS tracks before sending them to FG
 */
//////////////////////////////////////////////////////////////////////
//
// Smoothing algorithm is X_out(n) = ts * X_in(n + st) + (1-ts) * X_out(n-1)
//
// X_out -> smoothed parameter that is send to FG (e.g. position coordinate ...)
// X_in  -> parameter according to dead reckoning based on last DIS-PDU
//          the position based on this dead reckoning is not a current position but a position in future
//          with current position the smoothing would produce an offset based on current speed
//		    while with the used future position no permanent position offset results from smoothing
// st	 -> smoothing time, offset to the future that is used for dead reckoning
// ts    -> timestep between two messages to FG in seconds (sampling time)
// n	 -> (number of) current sample/FGMessage
// n-1   -> (number of) last sample/FGMessage (one timestep back in history)
//
// The entire algorithm can be related to the smoothing proposed in IEEE1278.2 with the modification that
// continuously the first step of that algorithm is done. 
//////////////////////////////////////////////////////////////////////
void FG_SERVER::smoothPDU(DIS::EntityStatePdu* drPDU, DIS::EntityStatePdu* smoothPDU, double timeStep){
	//smooth location
	smoothPDU->getEntityLocation().setX(timeStep * drPDU->getEntityLocation().getX() + (1.0-timeStep) * smoothPDU->getEntityLocation().getX());
	smoothPDU->getEntityLocation().setY(timeStep * drPDU->getEntityLocation().getY() + (1.0-timeStep) * smoothPDU->getEntityLocation().getY());
	smoothPDU->getEntityLocation().setZ(timeStep * drPDU->getEntityLocation().getZ() + (1.0-timeStep) * smoothPDU->getEntityLocation().getZ());
	//smooth orientation phi
	if( smoothPDU->getEntityOrientation().getPhi() - drPDU->getEntityOrientation().getPhi() > M_PI )
	{
		drPDU->getEntityOrientation().setPhi( drPDU->getEntityOrientation().getPhi() + 2*M_PI );
		smoothPDU->getEntityOrientation().setPhi(	timeStep * drPDU->getEntityOrientation().getPhi()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getPhi());

		if( smoothPDU->getEntityOrientation().getPhi() > M_PI )
		{
			smoothPDU->getEntityOrientation().setPhi( smoothPDU->getEntityOrientation().getPhi() - 2*M_PI );
		}
	}
	else if( smoothPDU->getEntityOrientation().getPhi() - drPDU->getEntityOrientation().getPhi() < -M_PI )
	{
		drPDU->getEntityOrientation().setPhi( drPDU->getEntityOrientation().getPhi() - 2*M_PI );
		smoothPDU->getEntityOrientation().setPhi(	timeStep * drPDU->getEntityOrientation().getPhi()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getPhi());

		if( smoothPDU->getEntityOrientation().getPhi() < -M_PI )
		{
			smoothPDU->getEntityOrientation().setPhi( smoothPDU->getEntityOrientation().getPhi() + 2*M_PI );
		}
	}
	else
	{
		smoothPDU->getEntityOrientation().setPhi(	timeStep * drPDU->getEntityOrientation().getPhi()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getPhi());
	}
	//smooth orientation theta
	if( smoothPDU->getEntityOrientation().getTheta() - drPDU->getEntityOrientation().getTheta() > M_PI )
	{
		drPDU->getEntityOrientation().setTheta( drPDU->getEntityOrientation().getTheta() + 2*M_PI );
		smoothPDU->getEntityOrientation().setTheta(	timeStep * drPDU->getEntityOrientation().getTheta()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getTheta());

		if( smoothPDU->getEntityOrientation().getTheta() > M_PI )
		{
			smoothPDU->getEntityOrientation().setTheta( smoothPDU->getEntityOrientation().getTheta() - 2*M_PI );
		}
	}
	else if( smoothPDU->getEntityOrientation().getTheta() - drPDU->getEntityOrientation().getTheta() < -M_PI )
	{
		drPDU->getEntityOrientation().setTheta( drPDU->getEntityOrientation().getTheta() - 2*M_PI );
		smoothPDU->getEntityOrientation().setTheta(	timeStep * drPDU->getEntityOrientation().getTheta()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getTheta());

		if( smoothPDU->getEntityOrientation().getTheta() < -M_PI )
		{
			smoothPDU->getEntityOrientation().setTheta( smoothPDU->getEntityOrientation().getTheta() + 2*M_PI );
		}
	}
	else
	{
		smoothPDU->getEntityOrientation().setTheta(	timeStep * drPDU->getEntityOrientation().getTheta()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getTheta());
	}
	//smooth orientation Psi
	if( smoothPDU->getEntityOrientation().getPsi() - drPDU->getEntityOrientation().getPsi() > M_PI )
	{
		drPDU->getEntityOrientation().setPsi( drPDU->getEntityOrientation().getPsi() + 2*M_PI );
		smoothPDU->getEntityOrientation().setPsi(	timeStep * drPDU->getEntityOrientation().getPsi()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getPsi());

		if( smoothPDU->getEntityOrientation().getPsi() > M_PI )
		{
			smoothPDU->getEntityOrientation().setPsi( smoothPDU->getEntityOrientation().getPsi() - 2*M_PI );
		}
	}
	else if( smoothPDU->getEntityOrientation().getPsi() - drPDU->getEntityOrientation().getPsi() < -M_PI )
	{
		drPDU->getEntityOrientation().setPsi( drPDU->getEntityOrientation().getPsi() - 2*M_PI );
		smoothPDU->getEntityOrientation().setPsi(	timeStep * drPDU->getEntityOrientation().getPsi()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getPsi());

		if( smoothPDU->getEntityOrientation().getPsi() < -M_PI )
		{
			smoothPDU->getEntityOrientation().setPsi( smoothPDU->getEntityOrientation().getPsi() + 2*M_PI );
		}
	}
	else
	{
		smoothPDU->getEntityOrientation().setPsi(	timeStep * drPDU->getEntityOrientation().getPsi()   + (1.0-timeStep) * smoothPDU->getEntityOrientation().getPsi());
	}
	//update velocities without smoothing
	smoothPDU->getEntityLinearVelocity().setX(drPDU->getEntityLinearVelocity().getX());
	smoothPDU->getEntityLinearVelocity().setY(drPDU->getEntityLinearVelocity().getY());
	smoothPDU->getEntityLinearVelocity().setZ(drPDU->getEntityLinearVelocity().getZ());
	//update accelerations without smoothing
	smoothPDU->getDeadReckoningParameters().getEntityLinearAcceleration().setX(drPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getX());
	smoothPDU->getDeadReckoningParameters().getEntityLinearAcceleration().setY(drPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getY());
	smoothPDU->getDeadReckoningParameters().getEntityLinearAcceleration().setZ(drPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getZ());
}//FG_SERVER::smoothPDU(DIS::EntityStatePdu* drPDU, DIS::EntityStatePdu* smoothPDU, double timeStep)
//////////////////////////////////////////////////////////////////////