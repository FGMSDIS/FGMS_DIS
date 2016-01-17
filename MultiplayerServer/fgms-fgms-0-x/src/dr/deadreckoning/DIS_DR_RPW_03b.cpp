// Generated from /DR/src/deadreckoning/DIS_DR_RPW_03b.java
#include <dr/deadreckoning/DIS_DR_RPW_03b.hpp>


template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

deadreckoning::DIS_DR_RPW_03b::DIS_DR_RPW_03b(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::DIS_DR_RPW_03b::DIS_DR_RPW_03b()
    : DIS_DR_RPW_03b(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void deadreckoning::DIS_DR_RPW_03b::run()
{
    try {
        while (true) {
            deltaCt++;
            ::java::lang::Thread::sleep(stall);
            entityLocation_X += entityLinearVelocity_X * changeDelta;
            entityLocation_Y += entityLinearVelocity_Y * changeDelta;
            entityLocation_Z += entityLinearVelocity_Z * changeDelta;
            entityOrientation_psi = std::fmod((entityOrientation_psi + entityAngularVelocity_X * changeDelta), (int32_t(2) * myPI));
            entityOrientation_theta = std::fmod((entityOrientation_theta + entityAngularVelocity_Y * changeDelta), (int32_t(2) * myPI));
            entityOrientation_phi = std::fmod((entityOrientation_phi + entityAngularVelocity_Z * changeDelta), (int32_t(2) * myPI));
        }
    } catch (::java::lang::Exception* e) {
        npc(::java::lang::System::out())->println(static_cast< ::java::lang::Object* >(e));
    }
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::DIS_DR_RPW_03b::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.DIS_DR_RPW_03b", 28);
    return c;
}

java::lang::Class* deadreckoning::DIS_DR_RPW_03b::getClass0()
{
    return class_();
}

