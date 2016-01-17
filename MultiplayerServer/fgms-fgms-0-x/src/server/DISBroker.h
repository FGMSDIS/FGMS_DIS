#if !defined DIS_BROKER_HXX
#define DIS_BROKER_HXX

#include "Quat.h"
#include <DIS/EntityStatePdu.h>
#include <DIS/FirePdu.h>
#include <DIS/ElectronicEmissionsPdu.h>
#include <flightgear/MultiPlayer/mpmessages.hxx>
#include <flightgear/MultiPlayer/tiny_xdr.hxx>
#include <time.h>
#include "fg_geometry.hxx"
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

		static DIS::EntityStatePdu createESPDU( T_MsgHdr* MsgHdr, T_PositionMsg* PosMsg, int forceID);
		static DIS::FirePdu DISBroker::createFPDU(DIS::EntityStatePdu MyEntity, DIS::EntityStatePdu Target, DIS::EntityType& type, int shoot_counter, unsigned int currentTime);
		static DIS::ElectronicEmissionsPdu DISBroker::createEEPDU(DIS::EntityStatePdu MyEntity, int emittingEventID,  unsigned int currentTime);
		static void DISBroker::createMPmessage(char* msg, DIS::EntityStatePdu &esPDU, string model, string CallSign, int bytes, double* updateRate, EntityTable	et, int forceID);

};//DISBroker

#endif