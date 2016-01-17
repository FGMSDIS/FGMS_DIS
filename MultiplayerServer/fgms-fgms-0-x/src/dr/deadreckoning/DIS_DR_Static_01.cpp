// Generated from /DR/src/deadreckoning/DIS_DR_Static_01.java
#include <deadreckoning/DIS_DR_Static_01.hpp>

deadreckoning::DIS_DR_Static_01::DIS_DR_Static_01(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::DIS_DR_Static_01::DIS_DR_Static_01()
    : DIS_DR_Static_01(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void deadreckoning::DIS_DR_Static_01::run()
{
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::DIS_DR_Static_01::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.DIS_DR_Static_01", 30);
    return c;
}

java::lang::Class* deadreckoning::DIS_DR_Static_01::getClass0()
{
    return class_();
}

