// Generated from /DR/src/deadreckoning/DIS_DR_RVW_04b.java
#include <deadreckoning/DIS_DR_RVW_04b.hpp>

#include <java/io/PrintStream.hpp>
#include <java/lang/Exception.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/Object.hpp>
#include <java/lang/System.hpp>
#include <java/lang/Thread.hpp>
#include <cmath>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

deadreckoning::DIS_DR_RVW_04b::DIS_DR_RVW_04b(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::DIS_DR_RVW_04b::DIS_DR_RVW_04b()
    : DIS_DR_RVW_04b(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void deadreckoning::DIS_DR_RVW_04b::run()
{
    try {
        while (true) {
            deltaCt++;
            ::java::lang::Thread::sleep(stall);
            entityLocation_X += (entityLinearVelocity_X * changeDelta) + (0.5 * entityLinearAcceleration_X * changeDelta* changeDelta);
            entityLocation_Y += (entityLinearVelocity_Y * changeDelta) + (0.5 * entityLinearAcceleration_Y * changeDelta* changeDelta);
            entityLocation_Z += (entityLinearVelocity_Z * changeDelta) + (0.5 * entityLinearAcceleration_Z * changeDelta* changeDelta);
            entityOrientation_psi = std::fmod((entityOrientation_psi + entityAngularVelocity_X * changeDelta), (int32_t(2) * myPI));
            entityOrientation_theta = std::fmod((entityOrientation_theta + entityAngularVelocity_Y * changeDelta), (int32_t(2) * myPI));
            entityOrientation_phi = std::fmod((entityOrientation_phi + entityAngularVelocity_Z * changeDelta), (int32_t(2) * myPI));
        }
    } catch (::java::lang::Exception* e) {
        npc(::java::lang::System::out())->println(static_cast< ::java::lang::Object* >(e));
    }
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::DIS_DR_RVW_04b::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.DIS_DR_RVW_04b", 28);
    return c;
}

java::lang::Class* deadreckoning::DIS_DR_RVW_04b::getClass0()
{
    return class_();
}

