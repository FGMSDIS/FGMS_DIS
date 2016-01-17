#pragma once


#include <DIS/EntityStatePdu.h>

class dr{

public:
	dr();
	virtual ~dr();
	void calcDR(DIS::EntityStatePdu *esPDU, double fps);

	}  ;
