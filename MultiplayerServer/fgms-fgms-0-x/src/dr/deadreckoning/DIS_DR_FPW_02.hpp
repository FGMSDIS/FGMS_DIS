// Generated from /DR/src/deadreckoning/DIS_DR_FPW_02.java

#pragma once

#include <deadreckoning/fwd-DR.hpp>
#include <deadreckoning/DIS_DeadReckoning.hpp>

struct default_init_tag;

class deadreckoning::DIS_DR_FPW_02
    : public DIS_DeadReckoning
{

public:
    typedef DIS_DeadReckoning super;
    void run() override;

    // Generated
    DIS_DR_FPW_02();
protected:
    DIS_DR_FPW_02(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
