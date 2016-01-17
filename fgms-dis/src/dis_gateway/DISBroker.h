#pragma once


#include "Quat.h"
#include <DIS/EntityStatePdu.h>
#include <flightgear/MultiPlayer/mpmessages.hxx>
#include <flightgear/MultiPlayer/tiny_xdr.hxx>
#include <time.h>
#include "fg_geometry.hxx"
//#include "fg_server.hxx"
#include <EntityTable.h>
#include <DIS/Vector3Double.h>


//////////////////////////////////////////////////////////////////////
//
//  Central class for processing DIS PDUs
//
//////////////////////////////////////////////////////////////////////
class DISBroker
{
	public:
		DISBroker(void);

		~DISBroker(void);

		DIS::EntityStatePdu createESPDU( T_MsgHdr* MsgHdr, T_PositionMsg* PosMsg );
		void createMPmessage(char* msg, DIS::EntityStatePdu &esPDU, string model, string CallSign, int bytes, double* updateRate);

};



