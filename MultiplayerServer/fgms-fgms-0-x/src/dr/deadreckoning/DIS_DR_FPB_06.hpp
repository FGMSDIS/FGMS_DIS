// Generated from /DR/src/deadreckoning/DIS_DR_FPB_06.java

#pragma once

#include <fwd-DR.hpp>
#include <deadreckoning/fwd-DR.hpp>
#include <deadreckoning/utils/fwd-DR.hpp>
#include <deadreckoning/DIS_DeadReckoning.hpp>

struct default_init_tag;

class deadreckoning::DIS_DR_FPB_06
    : public DIS_DeadReckoning
{

public:
    typedef DIS_DeadReckoning super;

public: /* package */
    ::deadreckoning::utils::Matrix* initInv {  };
    ::doubleArray* velVec {  };
    ::doubleArray* updated {  };

public:
    void run() override;

private:
    ::doubleArray* makeR1() /* throws(Exception) */;

    // Generated

public:
    DIS_DR_FPB_06();
protected:
    void ctor();
    DIS_DR_FPB_06(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
