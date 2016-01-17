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

// Copyright (C) 2005-2010  Oliver Schroeder
//

//////////////////////////////////////////////////////////////////////
//
//  server for FlightGear
//
//////////////////////////////////////////////////////////////////////

#if !defined FG_SERVER_HXX
#define FG_SERVER_HXX

#include <math.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <plib/netSocket.h>
#include <flightgear/MultiPlayer/mpmessages.hxx>
#include <flightgear/MultiPlayer/tiny_xdr.hxx>
#include <simgear/debug/logstream.hxx>
#include "daemon.hxx"
#include "fg_geometry.hxx"
#include "fg_list.hxx"
#include "fg_util.hxx"
#include "DISBroker.h"
#include "dr.h"
#include <DIS/EntityStatePdu.h>
#include <DIS/FirePdu.h>
#include <DIS/ElectronicEmissionsPdu.h>
#include <EntityTable.h>
#include <CallSignManager.h>
#include <winbase.h>
#include "DISMap.h"


using namespace std;

//////////////////////////////////////////////////////////////////////
/**
 * @class FG_SERVER
 * @brief The Main fgms Class
 */
class FG_SERVER
{
public:

	friend class FG_CLI;
	friend void *disLoop (void *arg);

	/** @brief Internal Constants */
	enum FG_SERVER_CONSTANTS
	{
		// return values
		SUCCESS                 = 0,
		ERROR_COMMANDLINE       = 1,
		ERROR_CREATE_SOCKET     = 2,
		ERROR_COULDNT_BIND      = 3,
		ERROR_NOT_LISTENING     = 4,
		ERROR_COULDNT_LISTEN    = 5,

		// other constants
		MAX_PACKET_SIZE         = 1200, // to agree with FG multiplayermgr.cxx (since before  2008)
		UPDATE_INACTIVE_PERIOD  = 1
	};
	//////////////////////////////////////////////////
	//
	//  constructors
	//
	//////////////////////////////////////////////////
	FG_SERVER ();
	~FG_SERVER ();

	//////////////////////////////////////////////////
	//
	//  public methods
	//
	//////////////////////////////////////////////////
	int   Init ();
	int   incomingMessageEvent_Loop ();
	void  Done ();

	void  PrepareInit ();
	void  SetFromFGPort ( int Port );
	void  SetDISPort ( int Port );
	void  SetDISSite ( int Site );
	void  SetDISAppl (int Application );
	void  SetForceID (int forceID);
	void  SetDIS2FGUpdaterate ( double FGUpdaterate );
	void  SetMyCallsign ( string callsign );
	void  SetPlayerExpires ( int Seconds );
	void  SetOutOfReach ( int OutOfReach );
	void  SetRadarActive ( bool activeRadar );
	void  SetServerName ( const std::string& ServerName );
	void  SetBindAddress ( const std::string& BindAddress );
	void  SetDISAddress ( const std::string& DISAddress );
	static void* receivePDU (void * This);
	static void* internalDIS2FG_Loop (void * This);
	
	PDUList		disMap;
	PDUList		disMapSmooth;
	PDUList		FG_Client;
	EntityTable	et;
	
	//////////////////////////////////////////////////
	//
	//  public variables
	//
	//////////////////////////////////////////////////
	string ConfigFile;

protected:

	//////////////////////////////////////////////////
	//
	//  private variables
	//
	//////////////////////////////////////////////////
	
	typedef std::map<uint32_t,string>		mT_IP2Relay;
	typedef std::map<uint32_t,string>::iterator	mT_RelayMapIt;
	bool		m_Initialized;
	bool		m_ReinitData;
	bool		m_ReinitDIS;
	bool		m_ReinitDISEntityTable;
	bool		m_Listening;
	bool		m_Debug;
	int		m_fromFGPort;
	int		m_DISPort;
	int		m_PlayerExpires;
	int		m_PlayerIsOutOfReach;
	int		m_DISSite;
	int		m_DISApplication;
	double	m_DIS2FGUpdaterate;
	unsigned short m_ProtocolVersion;
	unsigned short m_ExerciseID;
	unsigned short m_PDUtype;
	string		m_BindAddress;
	string		m_DISBindAddress;
	netAddress	m_DISAddress;
	DIS::DataStream m_DISbuffer;
	DIS::DataStream m_2ndDISbuffer;
	string		m_myDisKey;
	string		m_myCallsign;
	
	double		m_SmoothingTime; //timeconstant for asymptotoc closure between real and smoothed position in seconds
	size_t		m_NumMaxClients;
	string		m_ServerName;
	netSocket*	m_fromFGSocket;
	netSocket*	m_DISSocket;
	netSocket*	m_toFGSocket;
	PlayerList	m_PlayerList;
	int			m_ipcid;
	bool		m_radarActive;
	int			m_shootCounter;
	int			m_forceID;
	int			m_emittingEventID;
	/*int			m_stateUpdateIndicator;*/

	//////////////////////////////////////////////////
	//
	//  private methods
	//
	//////////////////////////////////////////////////
	void  AddClient     ( const netAddress& Sender, char* Msg );
	void  ReceiveFGPacket  ( char* sMsg, int Bytes,
	                      const netAddress& SenderAdress, unsigned int currentTime, unsigned int* nextHeartBeat );
	void  SendMPMessage  ( char* sMsg, int Bytes ); 
	bool  IsInRange     ( FG_ListElement& Relay,  FG_Player& SendingPlayer );
	string ToString(unsigned short wert);
	string addToDISMap( DIS::EntityStatePdu *esPDU);
	static void smoothPDU(DIS::EntityStatePdu* drPDU, DIS::EntityStatePdu* smoothPDU, double timeStep);
	
	
}; // FG_SERVER

#endif

