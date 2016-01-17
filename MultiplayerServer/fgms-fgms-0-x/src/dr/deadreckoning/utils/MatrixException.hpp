// Generated from /DR/src/deadreckoning/utils/MatrixException.java

#pragma once

#include <deadreckoning/utils/fwd-DR.hpp>
#include <java/lang/fwd-DR.hpp>
#include <java/lang/Exception.hpp>

struct default_init_tag;

class deadreckoning::utils::MatrixException
    : public ::java::lang::Exception
{

public:
    typedef ::java::lang::Exception super;
protected:
    void ctor(::java::lang::String* s);

    // Generated

public:
    MatrixException(::java::lang::String* s);
protected:
    MatrixException(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    virtual ::java::lang::Class* getClass0();
};
