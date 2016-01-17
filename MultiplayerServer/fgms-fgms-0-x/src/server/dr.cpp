#include <dr.h>
#include <Quat.h>


dr::dr(){
	}

dr::~dr()
	{
	}

//////////////////////////////////////////////////////////////////////
/**
 * @brief public method for Dead Reckoning according to IEEE1278.1
 */
void dr::calcDR(DIS::EntityStatePdu * esPDU, double elapsedTime ){
	switch(esPDU->getDeadReckoningParameters().getDeadReckoningAlgorithm()){
	case 1: break;
	case 2: PosFromVel(esPDU, elapsedTime);
			break;
	case 3: PosFromVel(esPDU, elapsedTime);
			Orientation(esPDU, elapsedTime); 
			break;
	case 4: PosFromVelAndAcc(esPDU, elapsedTime);
			Orientation(esPDU, elapsedTime); 
			break;
	case 5: PosFromVelAndAcc(esPDU, elapsedTime);
			break;
	//algorithms 6-9 are similiar to 2-5 but use a body centerd frame,
	//here they are calculated using the same procedures as 2-5
	//so algorithms 6-8 do not use the rotation information that is 
	//normally needed to calculate position in a body centered frame
	case 6: PosFromVel(esPDU, elapsedTime);
			break;
	case 7: PosFromVel(esPDU, elapsedTime);
			Orientation(esPDU, elapsedTime); 
			break;
	case 8: PosFromVelAndAcc(esPDU, elapsedTime);
			Orientation(esPDU, elapsedTime); 
			break;
	case 9: PosFromVelAndAcc(esPDU, elapsedTime);
			break;
	}
}

//////////////////////////////////////////////////////////////////////
/**
 * @brief updating position based on velocity
 */
void dr::PosFromVel(DIS::EntityStatePdu *esPDU, double elapsedTime){
	esPDU->getEntityLocation().setX(	esPDU->getEntityLocation().getX() 
									+	elapsedTime 
									  * esPDU->getEntityLinearVelocity().getX() 
									  );
	esPDU->getEntityLocation().setY(	esPDU->getEntityLocation().getY() 
									+	elapsedTime
									  * esPDU->getEntityLinearVelocity().getY() 
									  );
	esPDU->getEntityLocation().setZ(	esPDU->getEntityLocation().getZ() 
									+	elapsedTime
									  * esPDU->getEntityLinearVelocity().getZ() 
									  );
	}

//////////////////////////////////////////////////////////////////////
/**
 * @brief updating position based on velocitiy and acceleration
 */
void dr::PosFromVelAndAcc(DIS::EntityStatePdu *esPDU, double elapsedTime){
	esPDU->getEntityLocation().setX(	esPDU->getEntityLocation().getX() 
									+	elapsedTime 
									  * esPDU->getEntityLinearVelocity().getX() 
									+	0.5 
									  * elapsedTime 
									  * elapsedTime 
									  * esPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getX() 
									  );
	esPDU->getEntityLocation().setY(	esPDU->getEntityLocation().getY() 
									+	elapsedTime
									  * esPDU->getEntityLinearVelocity().getY() 
									+	0.5 
									  * elapsedTime
									  * elapsedTime
									  * esPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getY() 
									  );
	esPDU->getEntityLocation().setZ(	esPDU->getEntityLocation().getZ() 
									+	elapsedTime
									  * esPDU->getEntityLinearVelocity().getZ() 
									+	0.5
									  * elapsedTime
									  * elapsedTime
									  * esPDU->getDeadReckoningParameters().getEntityLinearAcceleration().getZ() 
									  );
	}

//////////////////////////////////////////////////////////////////////
/**
 * @brief updating entity orientation
 */
void dr::Orientation(DIS::EntityStatePdu *esPDU, double elapsedTime){
	//Update Orientation in 3 steps
	// step 1 create a quaternion for orientation and for delta orientation
	//		1.a orientation quaternion from euler angles
	Quat o = Quat::fromEulerRad(	esPDU->getEntityOrientation().getPsi(), 
								esPDU->getEntityOrientation().getTheta(), 
								esPDU->getEntityOrientation().getPhi());
	//		1.b delta orientation from angle axis of angular velocities
	Point3D aaAv = Point3D( esPDU->getDeadReckoningParameters().getEntityAngularVelocity().getX() * elapsedTime, 
							esPDU->getDeadReckoningParameters().getEntityAngularVelocity().getY() * elapsedTime, 
							esPDU->getDeadReckoningParameters().getEntityAngularVelocity().getZ() * elapsedTime);
	Quat od = Quat::fromAngleAxis( aaAv );
	// step	2 multiply both for successive rotations
	Quat sr = Quat::hamiltonProd( o, od );
	// step 3 get euler angles from resulting quaternion
	double psi, theta, phi;
	sr.getEulerRad(psi, theta, phi);
	//write updated values in esPDU
	esPDU->getEntityOrientation().setPsi(psi);
	esPDU->getEntityOrientation().setTheta(theta);
	esPDU->getEntityOrientation().setPhi(phi);
	}