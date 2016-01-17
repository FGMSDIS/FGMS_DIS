// Generated from /DR/src/deadreckoning/DIS_DR_FVW_05.java
#include <dr/deadreckoning/DIS_DR_FVW_05.hpp>
#include <iostream>

DIS_DR_FVW_05::DIS_DR_FVW_05(){
	
	}

void* DIS_DR_FVW_05::run(void*)
{
    while (true) {
        deltaCt++;
        entityLocation_X += (entityLinearVelocity_X * changeDelta) + (0.5 * entityLinearAcceleration_X * changeDelta* changeDelta);
        entityLocation_Y += (entityLinearVelocity_Y * changeDelta) + (0.5 * entityLinearAcceleration_Y * changeDelta* changeDelta);
        entityLocation_Z += (entityLinearVelocity_Z * changeDelta) + (0.5 * entityLinearAcceleration_Z * changeDelta* changeDelta);
    }
}

int main(){
	//pthread_t t1;
	//pthread_create(&t1, NULL, &run, NULL);
   return 0;
	}

