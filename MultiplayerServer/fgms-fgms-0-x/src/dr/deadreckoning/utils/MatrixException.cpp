// Generated from /DR/src/deadreckoning/utils/MatrixException.java
#include <deadreckoning/utils/MatrixException.hpp>

deadreckoning::utils::MatrixException::MatrixException(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::utils::MatrixException::MatrixException(::java::lang::String* s) 
    : MatrixException(*static_cast< ::default_init_tag* >(0))
{
    ctor(s);
}

void deadreckoning::utils::MatrixException::ctor(::java::lang::String* s)
{
    super::ctor(s);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::utils::MatrixException::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.utils.MatrixException", 35);
    return c;
}

java::lang::Class* deadreckoning::utils::MatrixException::getClass0()
{
    return class_();
}

