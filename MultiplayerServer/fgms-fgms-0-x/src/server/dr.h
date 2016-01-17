#pragma once

#include <dr/deadreckoning/DIS_DeadReckoning.hpp>
#include <dr/deadreckoning/DIS_DR_FVW_05.hpp>
#include <DIS/EntityStatePdu.h>

class dr{

public:
	dr();
	virtual ~dr();
	static void dr::calcDR(DIS::EntityStatePdu *esPDU, double elapsedTime);

private:
	static void dr::PosFromVel(DIS::EntityStatePdu *esPDU, double elapsedTime);
	static void dr::PosFromVelAndAcc(DIS::EntityStatePdu *esPDU, double elapsedTime);
	static void dr::Orientation(DIS::EntityStatePdu *esPDU, double elapsedTime);

	}  ;
