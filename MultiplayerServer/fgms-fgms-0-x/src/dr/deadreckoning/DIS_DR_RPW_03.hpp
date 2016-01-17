// Generated from /DR/src/deadreckoning/DIS_DR_RPW_03.java

#pragma once

#include <deadreckoning/fwd-DR.hpp>
#include <deadreckoning/utils/fwd-DR.hpp>
#include <deadreckoning/DIS_DeadReckoning.hpp>

struct default_init_tag;

class deadreckoning::DIS_DR_RPW_03
    : public DIS_DeadReckoning
{

public:
    typedef DIS_DeadReckoning super;

public: /* package */
    ::deadreckoning::utils::Matrix* ident {  };
    ::deadreckoning::utils::Matrix* DR {  };
    ::deadreckoning::utils::Matrix* DRR {  };

public:
    void run() override;

private:
    void makeThisDR() /* throws(Exception) */;

    // Generated

public:
    DIS_DR_RPW_03();
protected:
    void ctor();
    DIS_DR_RPW_03(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
