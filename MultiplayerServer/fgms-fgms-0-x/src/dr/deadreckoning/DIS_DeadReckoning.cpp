#include <dr/deadreckoning/DIS_DeadReckoning.hpp>



DIS_DeadReckoning::DIS_DeadReckoning()
{
}

void DIS_DeadReckoning::init()
{
    entityLinearVelocity_X = 0;
    entityLinearVelocity_Y = 0;
    entityLinearVelocity_Z = 0;
    entityLinearAcceleration_X = 0;
    entityLinearAcceleration_Y = 0;
    entityLinearAcceleration_Z = 0;
    entityAngularVelocity_X = 0;
    entityAngularVelocity_Y = 0;
    entityAngularVelocity_Z = 0;
    fps = 30;
    changeDelta = 1.0 / fps;
    deltaCt = 0;
    stall = (1000 / fps);
    myPI = 3.1415925;

}

DIS::EntityStatePdu getUpdatedESPDU(DIS::EntityStatePdu esPDU){

	return esPDU;
	}
void DIS_DeadReckoning::run(){


	}

/**Vector3Float DIS_DeadReckoning::getUpdatedPosition(){
	position = (entityLocation_X, entityLocation_Y, entityLocation_z);
    return position;
}

Vector3Float DIS_DeadReckoning::getUpdatedOrientation(){
	 ori = (entityOrientation_phi, entityOrientation_theta, entityOrientation_psi);
	 return	 ori;
}
		 
**/
void DIS_DeadReckoning::setFPS(float frames)
{
    fps = frames;
    changeDelta = 1 / fps;
}

void DIS_DeadReckoning::setNewAll(DIS::EntityStatePdu esPDU) /* throws(Exception) */
{
	entityLocation_X = esPDU.getEntityLocation().getX();
    entityLocation_Y = esPDU.getEntityLocation().getY();
    entityLocation_Z = esPDU.getEntityLocation().getZ();
    entityOrientation_psi = esPDU.getEntityOrientation().getPsi();
    entityOrientation_theta = esPDU.getEntityOrientation().getTheta();
    entityOrientation_phi = esPDU.getEntityOrientation().getPhi();
    entityLinearVelocity_X = esPDU.getEntityLinearVelocity().getX();
    entityLinearVelocity_Y = esPDU.getEntityLinearVelocity().getY();
    entityLinearVelocity_Z = esPDU.getEntityLinearVelocity().getZ();
    entityLinearAcceleration_X = esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getX();
    entityLinearAcceleration_Y = esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getY();
    entityLinearAcceleration_Z = esPDU.getDeadReckoningParameters().getEntityLinearAcceleration().getZ();
    entityAngularVelocity_X = esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getX();
    entityAngularVelocity_Y = esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getY();
    entityAngularVelocity_Z = esPDU.getDeadReckoningParameters().getEntityAngularVelocity().getZ();
	wMag = sqrt(entityAngularVelocity_X * entityAngularVelocity_X + entityAngularVelocity_Y * entityAngularVelocity_Y + entityAngularVelocity_Z * entityAngularVelocity_Z);
    wSq = wMag * wMag;
    //setOmega();
    //setWW();
    //setInitOrient();
    deltaCt = 0;
}

/* void deadreckoning::DIS_DeadReckoning::setInitOrient()  throws(Exception)
{
    auto cosPsi = ::java::lang::Math::cos(entityOrientation_psi);
    auto sinPsi = ::java::lang::Math::sin(entityOrientation_psi);
    auto cosTheta = ::java::lang::Math::cos(entityOrientation_theta);
    auto sinTheta = ::java::lang::Math::sin(entityOrientation_theta);
    auto cosPhi = ::java::lang::Math::cos(entityOrientation_phi);
    auto sinPhi = ::java::lang::Math::sin(entityOrientation_phi);
    npc(initOrien)->setCell(0, 0, cosTheta * cosPsi);
    npc(initOrien)->setCell(0, 1, cosTheta * sinPsi);
    npc(initOrien)->setCell(0, 2, -sinTheta);
    npc(initOrien)->setCell(1, 0, sinPhi * sinTheta * cosPsi - cosPhi * sinPsi);
    npc(initOrien)->setCell(1, 1, sinPhi * sinTheta * sinPsi + cosPhi * cosPsi);
    npc(initOrien)->setCell(1, 2, sinPhi * cosTheta);
    npc(initOrien)->setCell(2, 0, cosPhi * sinTheta * cosPsi + sinPhi * sinPsi);
    npc(initOrien)->setCell(2, 1, cosPhi * sinTheta * sinPsi - sinPhi * cosPsi);
    npc(initOrien)->setCell(2, 2, cosPhi * cosTheta);
}	 
**/

/*void deadreckoning::DIS_DeadReckoning::setWW()
{
    npc(ww)->setCell(0, 0, entityAngularVelocity_X * entityAngularVelocity_X);
    npc(ww)->setCell(0, 1, entityAngularVelocity_X * entityAngularVelocity_Y);
    npc(ww)->setCell(0, 2, entityAngularVelocity_X * entityAngularVelocity_Z);
    npc(ww)->setCell(1, 0, entityAngularVelocity_Y * entityAngularVelocity_X);
    npc(ww)->setCell(1, 1, entityAngularVelocity_Y * entityAngularVelocity_Y);
    npc(ww)->setCell(1, 2, entityAngularVelocity_Y * entityAngularVelocity_Z);
    npc(ww)->setCell(2, 0, entityAngularVelocity_Z * entityAngularVelocity_X);
    npc(ww)->setCell(2, 1, entityAngularVelocity_Z * entityAngularVelocity_Y);
    npc(ww)->setCell(2, 2, entityAngularVelocity_Z * entityAngularVelocity_Z);
}

void deadreckoning::DIS_DeadReckoning::setOmega()
{
    npc(skewOmega)->setCell(0, 0, 0);
    npc(skewOmega)->setCell(1, 1, 0);
    npc(skewOmega)->setCell(2, 2, 0);
    npc(skewOmega)->setCell(1, 0, entityAngularVelocity_Z);
    npc(skewOmega)->setCell(2, 0, -entityAngularVelocity_Y);
    npc(skewOmega)->setCell(2, 1, entityAngularVelocity_X);
    npc(skewOmega)->setCell(0, 1, -entityAngularVelocity_Z);
    npc(skewOmega)->setCell(0, 2, entityAngularVelocity_Y);
    npc(skewOmega)->setCell(1, 2, -entityAngularVelocity_X);
}
**/


