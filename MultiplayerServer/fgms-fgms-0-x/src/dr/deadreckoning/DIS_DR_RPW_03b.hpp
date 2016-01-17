// Generated from /DR/src/deadreckoning/DIS_DR_RPW_03b.java

#pragma once

#include <dr/deadreckoning/DIS_DeadReckoning.hpp>

struct default_init_tag;

class deadreckoning::DIS_DR_RPW_03b
    : public DIS_DeadReckoning
{

public:
    typedef DIS_DeadReckoning super;
    void run() override;

    // Generated
    DIS_DR_RPW_03b();
protected:
    DIS_DR_RPW_03b(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
