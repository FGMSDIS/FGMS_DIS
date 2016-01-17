

#pragma once

#include <dr/deadreckoning/DIS_DeadReckoning.hpp>


class DIS_DR_FVW_05: 
	public DIS_DeadReckoning
{

public:
    typedef DIS_DeadReckoning super;
	void* DIS_DR_FVW_05::run(void*);
	void* laeuft(void*);
	int main();

    // Generated
    DIS_DR_FVW_05();

};
