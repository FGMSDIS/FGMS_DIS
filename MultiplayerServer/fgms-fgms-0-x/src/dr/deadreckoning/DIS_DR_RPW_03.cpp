// Generated from /DR/src/deadreckoning/DIS_DR_RPW_03.java
#include <deadreckoning/DIS_DR_RPW_03.hpp>

#include <deadreckoning/utils/Matrix.hpp>
#include <java/io/PrintStream.hpp>
#include <java/lang/Double.hpp>
#include <java/lang/Exception.hpp>
#include <java/lang/Math.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/Object.hpp>
#include <java/lang/System.hpp>
#include <java/lang/Thread.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

deadreckoning::DIS_DR_RPW_03::DIS_DR_RPW_03(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::DIS_DR_RPW_03::DIS_DR_RPW_03()
    : DIS_DR_RPW_03(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void deadreckoning::DIS_DR_RPW_03::ctor()
{
    super::ctor();
    init();
}

void deadreckoning::DIS_DR_RPW_03::init()
{
    ident = new ::deadreckoning::utils::Matrix(int32_t(3));
    DR = new ::deadreckoning::utils::Matrix(int32_t(3));
    DRR = new ::deadreckoning::utils::Matrix(int32_t(3));
}

void deadreckoning::DIS_DR_RPW_03::run()
{
    try {
        while (true) {
            deltaCt++;
            ::java::lang::Thread::sleep(stall);
            entityLocation_X += entityLinearVelocity_X * changeDelta;
            entityLocation_Y += entityLinearVelocity_Y * changeDelta;
            entityLocation_Z += entityLinearVelocity_Z * changeDelta;
            makeThisDR();
            DRR = ::deadreckoning::utils::Matrix::mult(DR, initOrien);
            entityOrientation_theta = static_cast< float >(::java::lang::Math::asin(-npc(DRR)->cell(0, 2)));
            entityOrientation_psi = static_cast< float >((::java::lang::Math::acos(npc(DRR)->cell(0, 0) / ::java::lang::Math::cos(entityOrientation_theta)) * ::java::lang::Math::signum(npc(DRR)->cell(0, 1))));
            entityOrientation_phi = static_cast< float >((::java::lang::Math::acos(npc(DRR)->cell(2, 2) / ::java::lang::Math::cos(entityOrientation_theta)) * ::java::lang::Math::signum(npc(DRR)->cell(1, 2))));
            if(::java::lang::Double::isNaN(entityOrientation_psi))
                entityOrientation_psi = 0;

            if(::java::lang::Double::isNaN(entityOrientation_theta))
                entityOrientation_theta = 0;

            if(::java::lang::Double::isNaN(entityOrientation_phi))
                entityOrientation_phi = 0;

        }
    } catch (::java::lang::Exception* e) {
        npc(::java::lang::System::out())->println(static_cast< ::java::lang::Object* >(e));
    }
}

void deadreckoning::DIS_DR_RPW_03::makeThisDR() /* throws(Exception) */
{
    auto wDelta = wMag * changeDelta * deltaCt;
    auto cosWdelta = ::java::lang::Math::cos(wDelta);
    auto wwScale = (int32_t(1) - cosWdelta) / wSq;
    auto identScalar = cosWdelta;
    auto skewScale = ::java::lang::Math::sin(wDelta) / wMag;
    auto wwTmp = npc(ww)->mult(wwScale);
    auto identTmp = npc(ident)->mult(identScalar);
    auto skwTmp = npc(skewOmega)->mult(skewScale);
    DR = ::deadreckoning::utils::Matrix::add(wwTmp, identTmp);
    DR = ::deadreckoning::utils::Matrix::subtract(DR, skwTmp);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::DIS_DR_RPW_03::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.DIS_DR_RPW_03", 27);
    return c;
}

java::lang::Class* deadreckoning::DIS_DR_RPW_03::getClass0()
{
    return class_();
}

