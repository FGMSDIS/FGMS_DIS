#pragma once

#include <iostream>
#include <vector>
#include <DIS/EntityStatePdu.h>
#include <DIS/Vector3Float.h>
#include <math.h>
#include <pthread.h>



class DIS_DeadReckoning
{

protected: /* protected */
    double entityLocation_X;
    double entityLocation_Y;
    double entityLocation_Z;
    float entityOrientation_psi;
    float entityOrientation_theta;
    float entityOrientation_phi;
    float entityLinearVelocity_X;
    float entityLinearVelocity_Y;
    float entityLinearVelocity_Z;
    float entityLinearAcceleration_X;
    float entityLinearAcceleration_Y;
    float entityLinearAcceleration_Z;
    float entityAngularVelocity_X;
    float entityAngularVelocity_Y;
    float entityAngularVelocity_Z;
    float fps;
    float changeDelta;
    int deltaCt;
    int stall;
	pthread_t aThread;

public:
	//Vector3Float ori;
    //Vector3Float position;
    double wMag;
    double wSq;
    float myPI;

	DIS::EntityStatePdu getUpdatedESPDU(DIS::EntityStatePdu esPDU);
    void setFPS(float frames);
	void setNewAll(DIS::EntityStatePdu esPDU);
	void DIS_DeadReckoning::init();
	void DIS_DeadReckoning::run();

    // Generated
    DIS_DeadReckoning();
};
