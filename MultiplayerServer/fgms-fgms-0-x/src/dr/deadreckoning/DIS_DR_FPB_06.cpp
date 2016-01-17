// Generated from /DR/src/deadreckoning/DIS_DR_FPB_06.java
#include <deadreckoning/DIS_DR_FPB_06.hpp>

#include <deadreckoning/utils/Matrix.hpp>
#include <java/io/PrintStream.hpp>
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

deadreckoning::DIS_DR_FPB_06::DIS_DR_FPB_06(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::DIS_DR_FPB_06::DIS_DR_FPB_06()
    : DIS_DR_FPB_06(*static_cast< ::default_init_tag* >(0))
{
    ctor();
}

void deadreckoning::DIS_DR_FPB_06::ctor()
{
    super::ctor();
    init();
}

void deadreckoning::DIS_DR_FPB_06::init()
{
    velVec = (new ::doubleArray({
        static_cast< double >(entityLinearVelocity_X)
        , static_cast< double >(entityLinearVelocity_Y)
        , static_cast< double >(entityLinearVelocity_Z)
    }));
}

void deadreckoning::DIS_DR_FPB_06::run()
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
        }
    } catch (::java::lang::Exception* e) {
        npc(::java::lang::System::out())->println(static_cast< ::java::lang::Object* >(e));
    }
}

doubleArray* deadreckoning::DIS_DR_FPB_06::makeR1() /* throws(Exception) */
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

java::lang::Class* deadreckoning::DIS_DR_FPB_06::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.DIS_DR_FPB_06", 27);
    return c;
}

java::lang::Class* deadreckoning::DIS_DR_FPB_06::getClass0()
{
    return class_();
}

