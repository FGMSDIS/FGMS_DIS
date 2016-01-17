#include <dr.h>


dr::dr(){
	}

dr::~dr()
	{
	}


void dr::calcDR(DIS::EntityStatePdu * esPDU, double fps){

    double changeDelta =  fps;

	
	//DIS_DeadReckoning* deadr = new DIS_DR_FVW_05();
	double entityLocation_X	= esPDU->getEntityLocation().getX();
	double entityLocation_Y	= esPDU->getEntityLocation().getY();
	double entityLocation_Z	= esPDU->getEntityLocation().getZ();

	entityLocation_X += (esPDU->getEntityLinearVelocity().getX()  * changeDelta) + (0.5 * esPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getX() * changeDelta * changeDelta);
    entityLocation_Y += (esPDU->getEntityLinearVelocity().getY()  * changeDelta) + (0.5 * esPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getY() * changeDelta * changeDelta);
	entityLocation_Z += (esPDU->getEntityLinearVelocity().getZ()  * changeDelta) + (0.5 * esPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getZ() * changeDelta * changeDelta);
	
	esPDU->getEntityLocation().setX(entityLocation_X);
	esPDU->getEntityLocation().setY(entityLocation_Y);
	esPDU->getEntityLocation().setZ(entityLocation_Z);

	}