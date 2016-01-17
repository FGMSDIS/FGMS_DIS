// Generated from /DR/src/deadreckoning/DIS_DR_RPB_07.java
#include <DIS_DR_RPB_07.hpp>


template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

deadreckoning::DIS_DR_RPB_07::DIS_DR_RPB_07(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::DIS_DR_RPB_07::DIS_DR_RPB_07()
    : DIS_DR_RPB_07(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void deadreckoning::DIS_DR_RPB_07::ctor()
{
    super::ctor();
    init();
}

void deadreckoning::DIS_DR_RPB_07::init()
{
    ident = new ::deadreckoning::utils::Matrix(int32_t(3));
    DR = new ::deadreckoning::utils::Matrix(int32_t(3));
    DRR = new ::deadreckoning::utils::Matrix(int32_t(3));
    velVec = (new ::doubleArray({
        static_cast< double >(entityLinearVelocity_X)
        , static_cast< double >(entityLinearVelocity_Y)
        , static_cast< double >(entityLinearVelocity_Z)
    }));
    updated = new ::doubleArray(int32_t(3));
}

void deadreckoning::DIS_DR_RPB_07::run()
{
    try {
        initInv = ::deadreckoning::utils::Matrix::transpose(initOrien);
        while (true) {
            deltaCt++;
            ::java::lang::Thread::sleep(stall);
            updated = ::deadreckoning::utils::Matrix::multVec(initInv, makeR1());
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

void deadreckoning::DIS_DR_RPB_07::makeThisDR() /* throws(Exception) */
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

doubleArray* deadreckoning::DIS_DR_RPB_07::makeR1() /* throws(Exception) */
{
    auto R1 = new ::deadreckoning::utils::Matrix(int32_t(3));
    auto ident = new ::deadreckoning::utils::Matrix(int32_t(3));
    auto wDelta = wMag * changeDelta * deltaCt;
    auto wwScale = (wDelta - ::java::lang::Math::sin(wDelta)) / (wSq * wMag);
    auto identScalar = ::java::lang::Math::sin(wDelta) / wMag;
    auto skewScale = int32_t(1) - (::java::lang::Math::cos(wDelta) / wSq);
    auto wwTmp = npc(ww)->mult(wwScale);
    auto identTmp = npc(ident)->mult(identScalar);
    auto skwTmp = npc(skewOmega)->mult(skewScale);
    R1 = ::deadreckoning::utils::Matrix::add(wwTmp, identTmp);
    R1 = ::deadreckoning::utils::Matrix::subtract(R1, skwTmp);
    return ::deadreckoning::utils::Matrix::multVec(R1, velVec);
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::DIS_DR_RPB_07::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.DIS_DR_RPB_07", 27);
    return c;
}

java::lang::Class* deadreckoning::DIS_DR_RPB_07::getClass0()
{
    return class_();
}

