// Generated from /DR/src/deadreckoning/DIS_DR_RVB_08.java
#include <deadreckoning/DIS_DR_RVB_08.hpp>

#include <deadreckoning/utils/Matrix.hpp>
#include <java/io/PrintStream.hpp>
#include <java/lang/Double.hpp>
#include <java/lang/Exception.hpp>
#include <java/lang/Math.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/Object.hpp>
#include <java/lang/System.hpp>
#include <java/lang/Thread.hpp>
#include <Array.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

deadreckoning::DIS_DR_RVB_08::DIS_DR_RVB_08(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::DIS_DR_RVB_08::DIS_DR_RVB_08()
    : DIS_DR_RVB_08(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void deadreckoning::DIS_DR_RVB_08::ctor()
{
    super::ctor();
    init();
}

void deadreckoning::DIS_DR_RVB_08::init()
{
    DR = new ::deadreckoning::utils::Matrix(int32_t(3));
    DRR = new ::deadreckoning::utils::Matrix(int32_t(3));
    velVec = (new ::doubleArray({
        static_cast< double >(entityLinearVelocity_X)
        , static_cast< double >(entityLinearVelocity_Y)
        , static_cast< double >(entityLinearVelocity_Z)
    }));
    angVec = (new ::doubleArray({
        static_cast< double >(entityAngularVelocity_X)
        , static_cast< double >(entityAngularVelocity_Y)
        , static_cast< double >(entityAngularVelocity_Z)
    }));
    updated1 = new ::doubleArray(int32_t(3));
    updated2 = new ::doubleArray(int32_t(3));
    updated = new ::doubleArray(int32_t(3));
}

void deadreckoning::DIS_DR_RVB_08::run()
{
    try {
        initInv = ::deadreckoning::utils::Matrix::transpose(initOrien);
        while (true) {
            deltaCt++;
            ::java::lang::Thread::sleep(stall);
            updated1 = makeR1();
            updated2 = makeR2();
            (*updated)[int32_t(0)] = (*updated1)[int32_t(0)] + (*updated2)[int32_t(0)];
            (*updated)[int32_t(1)] = (*updated1)[int32_t(1)] + (*updated2)[int32_t(1)];
            (*updated)[int32_t(2)] = (*updated1)[int32_t(2)] + (*updated2)[int32_t(2)];
            updated = ::deadreckoning::utils::Matrix::multVec(initInv, updated);
            entityLocation_X += (*updated)[int32_t(0)];
            entityLocation_Y += (*updated)[int32_t(1)];
            entityLocation_Z += (*updated)[int32_t(2)];
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

void deadreckoning::DIS_DR_RVB_08::makeThisDR() /* throws(Exception) */
{
    auto ident = new ::deadreckoning::utils::Matrix(int32_t(3));
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

doubleArray* deadreckoning::DIS_DR_RVB_08::makeR2() /* throws(Exception) */
{
    auto R2 = new ::deadreckoning::utils::Matrix(int32_t(3));
    auto ident = new ::deadreckoning::utils::Matrix(int32_t(3));
    auto wDelta = wMag * changeDelta * deltaCt;
    auto wwScale = 0.5 * wSq * changeDelta* deltaCt* changeDelta* deltaCt;
    wwScale -= ::java::lang::Math::cos(wDelta);
    wwScale -= wDelta * ::java::lang::Math::sin(wDelta);
    wwScale++;
    wwScale /= wSq * wSq;
    auto identScalar = ::java::lang::Math::cbrt(wDelta) + wDelta * ::java::lang::Math::sin(wDelta) - int32_t(1);
    identScalar /= wSq;
    auto skewScale = ::java::lang::Math::sin(wDelta) - wDelta * ::java::lang::Math::cos(wDelta);
    skewScale /= wSq * wMag;
    auto wwTmp = npc(ww)->mult(wwScale);
    auto identTmp = npc(ident)->mult(identScalar);
    auto skwTmp = npc(skewOmega)->mult(skewScale);
    R2 = ::deadreckoning::utils::Matrix::add(wwTmp, identTmp);
    R2 = ::deadreckoning::utils::Matrix::add(R2, skwTmp);
    return ::deadreckoning::utils::Matrix::multVec(R2, angVec);
}

doubleArray* deadreckoning::DIS_DR_RVB_08::makeR1() /* throws(Exception) */
{
    auto R1 = new ::deadreckoning::utils::Matrix(int32_t(3));
    auto ident = new ::deadreckoning::utils::Matrix(int32_t(3));
    auto wDelta = wMag * changeDelta * deltaCt;
    auto wwScale = (wDelta - ::java::lang::Math::sin(wDelta)) / (wSq * wMag);
    auto identScalar = ::java::lang::Math::sin(wDelta) / wMag;
    auto skewScale = (int32_t(1) - ::java::lang::Math::cos(wDelta)) / wSq;
    auto wwTmp = npc(ww)->mult(wwScale);
    auto identTmp = npc(ident)->mult(identScalar);
    auto skwTmp = npc(skewOmega)->mult(skewScale);
    R1 = ::deadreckoning::utils::Matrix::add(wwTmp, identTmp);
    R1 = ::deadreckoning::utils::Matrix::subtract(R1, skwTmp);
    return ::deadreckoning::utils::Matrix::multVec(R1, velVec);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::DIS_DR_RVB_08::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.DIS_DR_RVB_08", 27);
    return c;
}

java::lang::Class* deadreckoning::DIS_DR_RVB_08::getClass0()
{
    return class_();
}

