/**
 * @file mpmessages.hxx 
 * @author  Duncan McCreanor
 * 
 * @brief Message definitions for multiplayer communications
 *        within multiplayer Flightgear
 * 
 * - Each message used for multiplayer communications consists of a header
 *   and optionally a block of data. 
 * - The combined header and data is sent as one IP packet, \ref xdr encoded.
 *  @note 
 * 		XDR demands 4 byte alignment, but some compilers use 8 byte
 * 		alignment, so it's safe to let the overall size of a network
 * 		message be a multiple of 8! 
 */

//
//  Written by Duncan McCreanor, started February 2003.
// duncan.mccreanor@airservicesaustralia.com
//
// Copyright (C) 2003  Airservices Australia
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
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef MPMESSAGES_H
#define MPMESSAGES_H

#include <vector>
#include <simgear/compiler.h>
#include <simgear/math/SGMath.hxx>
#include "tiny_xdr.hxx"
#include <map>
#include <DIS/EntityStatePdu.h>
#include <DIS/FirePdu.h>
#include "DISMap.h"
#include <EntityTable.h>

/** @brief The `Magic` value for message (currently FGFS). The magic is at
 * the start of every packet and is used for packet validation.
 */
const uint32_t MSG_MAGIC = 0x46474653;  // "FGFS"

/** @brief  The MP protocol version that is send with each packet
 * (currently 1.1).
 */
const uint32_t PROTO_VER = 0x00010001;  // 1.1

/** @brief  ID  of a "position" message, and the most trafficked */
#define POS_DATA_ID             7

/** @brief  Maximum length of a callsign */
#define MAX_CALLSIGN_LEN        8

/** @brief  Maximum length of a chat message 
 */
#define MAX_CHAT_MSG_LEN        256

/** @brief  Maximum length of a model name, eg /model/x17/aero-123.xml */
#define MAX_MODEL_NAME_LEN      96

/** @brief  Maximum length of property */
#define MAX_PROPERTY_LEN        52


/** 
 * @struct T_MsgHdr
 * @brief The header sent as the first part of all mp message packets.
 * 
 * The header is expected to have the correct ::MSG_MAGIC and ::PROTO_VER
 * and is checked upon in FG_SERVER::PacketIsValid
 */
struct T_MsgHdr
{
	/** @brief Magic Value */
	xdr_data_t  Magic;   
	/** @brief Protocol version */
	xdr_data_t  Version;           
	/** @brief Message identifier  */
	xdr_data_t  MsgId;     
	/** @brief Absolute length of message */
	xdr_data_t  MsgLen;    
	/** @brief Player's receiver address
	 * @deprecated Not used in current implementation
	 * set to zero
	 */
	xdr_data_t  ReplyAddress;   
	/** @brief Player's receiver port
	 * @deprecated Not used in current implementation
	 * set to zero
	 */
	xdr_data_t  ReplyPort;   
	/** @brief Callsign used by the player */
	char Name[MAX_CALLSIGN_LEN]; 
};

/** 
 * @struct T_PositionMsg
 * @brief A Position Message
 */
struct T_PositionMsg
{
	/** @brief  Name of the aircraft model */
	char Model[MAX_MODEL_NAME_LEN]; 
	/** @brief Time when this packet was generated */
	xdr_data2_t time;
	/** @brief Time when this packet was generated */
	xdr_data2_t lag;
	/** @brief Position wrt the earth centered frame */
	xdr_data2_t position[3];
	/** @brief Orientation wrt the earth centered frame, stored in
	 * the angle axis representation where the angle is coded into
	 * the axis length
	 */
	xdr_data_t orientation[3];
	/** @brief Linear velocity wrt the earth centered frame measured in
	 *         the earth centered frame
	 */
	xdr_data_t linearVel[3];
	/** @brief Angular velocity wrt the earth centered frame measured in
	 *          the earth centered frame
	 */
	xdr_data_t angularVel[3];
	/** @brief Linear acceleration wrt the earth centered frame measured
	 *         in the earth centered frame
	 */
	xdr_data_t linearAccel[3];
	/** @brief Angular acceleration wrt the earth centered frame measured
	 *         in the earth centered frame
	 */
	xdr_data_t angularAccel[3];
};

/** 
 * @struct T_PropertyMsg 
 * @brief Property Message 
 */
struct T_PropertyMsg
{
	xdr_data_t id;
	xdr_data_t value;
};

/**
 * @struct FGFloatPropertyData  
 * @brief Property Data 
 */
struct FGFloatPropertyData
{
	unsigned id;
	float value;
};

/** @brief Motion Message */
struct FGExternalMotionData
{
	/** 
	 * @brief Simulation time when this packet was generated 
	 */
	double time;
	// the artificial lag the client should stay behind the average
	// simulation time to arrival time difference
	// FIXME: should be some 'per model' instead of 'per packet' property
	double lag;
	/** 
	*  Position wrt the earth centered frame  
	*/
	SGVec3d position;
	/** @brief Orientation wrt the earth centered frame */
	SGQuatf orientation;
	/**
	* @brief Linear velocity wrt the earth centered frame measured in
	*        the earth centered frame
	*/
	SGVec3f linearVel;
	/** 
	* @brief Angular velocity wrt the earth centered frame measured in the earth centered frame
	*/
	SGVec3f angularVel;
	/** @brief Linear acceleration wrt the earth centered frame measured in the earth centered frame */
	SGVec3f linearAccel;
	/** @brief Angular acceleration wrt the earth centered frame measured in the earth centered frame */
	SGVec3f angularAccel;
	/** @brief The set of properties recieved for this timeslot */
	std::vector<FGFloatPropertyData> properties;
};

class MSG2ndPart
{
private:
	std::map <int,char*> myValueMap;

	inline unsigned int swap_32bit(unsigned int ui)
	{
		return (unsigned int)( 
							((ui & 0xFF000000) >> 24) | 
							((ui & 0x00FF0000) >> 8)  |								 
							((ui & 0x0000FF00) << 8)  |
							((ui & 0x000000FF) << 24)) ;									
	}

public:
	MSG2ndPart(char* msg, int bytes)
	{
		char* cp=msg+sizeof(T_MsgHdr)+sizeof(T_PositionMsg);
		int id;
		int stringlaenge;	

		while (cp<(msg+bytes))
		{
			id = swap_32bit(*(int*)cp);
			myValueMap[id]=cp+4;
			
			/*if(id < 100 || id > 10319)
			{
				std::cout<<"Stusswerte";
				for (int i=-20; i<50; i++)
				{
					std::cout<<(int)(cp+i)<<"-"<<(int)*(cp+i)<<"-"<<*(cp+i)<<"\n";
				}
			}*/

			if((id == 108) || (id == 905) || (id == 1101) || (id == 1200) || (id == 1400) || (id>=10001 && id<=10119))				// if(string)
			{
				int offset;
				// Länge bestimmen
				// id überspringen -> cp+=4
				stringlaenge = swap_32bit(*(int*)(cp+4));
				// id+lentgh+string+padding
				if (stringlaenge == 0) // leerer String
				{
					offset = 8;
				}
				else if (stringlaenge%4 == 0) //String mit 4*n Werten ohne Padding
				{
					offset = 8 + 4 * stringlaenge;
				}
				else // String mit 4*n+r Werten mit Padding von 4-r
				{
					offset = 8 + 4  * (stringlaenge+(4-stringlaenge%4));
				}
				cp+=offset;

			}
			else
			{
				// bool, int, float -> 8bytes
				cp+=8;
			}
		}
	}

	bool getBool(int key)
	{
		return *(bool*)(myValueMap[key]+3);
	}

	int getInt(int key)
	{
		if(myValueMap.find(key) != myValueMap.end())
		{
			return swap_32bit(*(int*)(myValueMap[key]));
		}
		else
		{
			return 0;
		}
	}

	float getFloat(int key)
	{
		char buffer [4];
		buffer[3] = *(myValueMap[key]);
		buffer[2] = *(myValueMap[key]+1);
		buffer[1] = *(myValueMap[key]+2);
		buffer[0] = *(myValueMap[key]+3);
		return *(float*)&buffer;
	}

	string getString(int key)
	{
		int stringlaenge = swap_32bit(*(int*)(myValueMap[key]));
		string s;
		for(int i=0; i<stringlaenge;i++)
		{
			s.append(myValueMap[key]+7+i*4);
		}
		return s ;
	}

	bool getFireSolution(DIS::EntityStatePdu& Target, DIS::EntityType& type, int& shoot_counter, PDUList disMap, EntityTable et)
	{
		bool Valid = false;
		// Fire solution is contained in chat string in MP-Message
		// Fire solution string is formatted "FIRE:<count>:<callsign>:<munitionType>"
		// with "FIRE" being the key to indicate firesolution compared to normal chat content
		// <count> being the number of the fire solution
		// <callsign> being the FG callsing and
		// <munitionType> being the name of the munition according to the entity table
		// and ":" being a separation symbol
		string ChatString = getString(10002);
		// Fire Solution Content
		// FireSolCont[0] = "FIRE"
		// FireSolCont[1] = <count>
		// FireSolCont[2] = <callsign>
		// FireSolCont[3] = <munitionType>
		string* FireSolCont[4];
		// iterator for FireSolCont
		int i = 0;
		while(ChatString.length()>0 && i<4)
		{
			int seppos = ChatString.find_first_of(":"); // Find Position of Seperation Symbol
			FireSolCont[i] = new string(ChatString.substr(0, seppos )); // read string until Sepration Symbol
			ChatString = ChatString.substr(seppos + 1 , ChatString.size() ); // cut string at Seperation Symbol
			i++;
		}
		if(i==4)
		{
			if(*(FireSolCont[0]) == "FIRE")
			{
				try
				{
					int fgshoot_counter = stoi(*(FireSolCont[1]));
					if(fgshoot_counter > shoot_counter) // new fire solution
					{
						shoot_counter = fgshoot_counter;
					}
					else if(fgshoot_counter < shoot_counter)// FG restart
					{
						shoot_counter = fgshoot_counter;
					}
					else //old fire solution
					{
						return false;
					}
					std::map<string, DIS::EntityStatePdu>::iterator disMapIter = disMap.find ( *(FireSolCont[2]) );
					if (disMapIter != disMap.end() )
					{
						DIS::EntityType* myType= et.getDISModelFromModelName(*(FireSolCont[3]));
						if(myType != NULL)
						{
							//Fire Solution contains valid content
							//get entity id fromd disMap
							type = *myType;
							Target = disMapIter->second;
							Valid = true;
						}
						else
						{
							cout << "Fire Solution contains Munition that is not found in entity table." << endl;
						}
					}
					else
					{
						cout << "Fire Solution contains invalid callsign." << endl;
					}
				}
				catch(const std::invalid_argument& ia)
				{
					cout << "Fire Solution contains invalid counter." << endl;
				}
			}
		}
		return Valid;
	}
};

#endif

