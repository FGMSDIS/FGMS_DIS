// Generated from /DR/src/deadreckoning/DIS_DR_FPW_02.java
#include <deadreckoning/DIS_DR_FPW_02.hpp>

#include <java/lang/Exception.hpp>
#include <java/lang/Thread.hpp>

deadreckoning::DIS_DR_FPW_02::DIS_DR_FPW_02(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::DIS_DR_FPW_02::DIS_DR_FPW_02()
    : DIS_DR_FPW_02(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void deadreckoning::DIS_DR_FPW_02::run()
{
    while (true) {
        deltaCt++;
        try {
            ::java::lang::Thread::sleep(stall);
        } catch (::java::lang::Exception* e) {
        }
        entityLocation_X += entityLinearVelocity_X * changeDelta;
        entityLocation_Y += entityLinearVelocity_Y * changeDelta;
        entityLocation_Z += entityLinearVelocity_Z * changeDelta;
    }
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::DIS_DR_FPW_02::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.DIS_DR_FPW_02", 27);
    return c;
}

java::lang::Class* deadreckoning::DIS_DR_FPW_02::getClass0()
{
    return class_();
}

