// Generated from /DR/src/deadreckoning/DIS_DR_FVB_09.java

#pragma once

#include <fwd-DR.hpp>
#include <deadreckoning/fwd-DR.hpp>
#include <deadreckoning/utils/fwd-DR.hpp>
#include <deadreckoning/DIS_DeadReckoning.hpp>

struct default_init_tag;

class deadreckoning::DIS_DR_FVB_09
    : public DIS_DeadReckoning
{

public:
    typedef DIS_DeadReckoning super;

public: /* package */
    ::deadreckoning::utils::Matrix* initInv {  };
    ::doubleArray* velVec {  };
    ::doubleArray* angVec {  };
    ::doubleArray* updated1 {  };
    ::doubleArray* updated2 {  };
    ::doubleArray* updated {  };

public:
    void run() override;

private:
    ::doubleArray* makeR2() /* throws(Exception) */;
    ::doubleArray* makeR1() /* throws(Exception) */;

    // Generated

public:
    DIS_DR_FVB_09();
protected:
    void ctor();
    DIS_DR_FVB_09(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
