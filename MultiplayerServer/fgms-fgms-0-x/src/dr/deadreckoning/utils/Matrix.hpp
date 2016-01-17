// Generated from /DR/src/deadreckoning/utils/Matrix.java

#pragma once

#include <fwd-DR.hpp>
#include <deadreckoning/utils/fwd-DR.hpp>
#include <java/io/fwd-DR.hpp>
#include <java/lang/fwd-DR.hpp>
#include <java/lang/Object.hpp>

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java
{
    namespace io
    {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
    } // io

    namespace lang
    {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
    } // lang
} // java

namespace 
{
typedef ::SubArray< ::doubleArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > doubleArrayArray;
} // 

struct default_init_tag;

class deadreckoning::utils::Matrix
    : public virtual ::java::lang::Object
{

public:
    typedef ::java::lang::Object super;

private:
    ::doubleArrayArray* data {  };
    double epsilon {  };
protected:
    void ctor(int32_t dimension);
    void ctor(int32_t rows, int32_t cols);
    void ctor(Matrix* M) /* throws(MatrixException) */;

public:
    virtual void replace(Matrix* M) /* throws(MatrixException) */;
    virtual int32_t cols();
    virtual int32_t rows();
    virtual double cell(int32_t i, int32_t j) /* throws(MatrixException) */;
    virtual void setCell(int32_t i, int32_t j, double value) /* throws(MatrixException) */;
    virtual Matrix* add(Matrix* M2) /* throws(MatrixException) */;
    static void add(Matrix* r1, double a) /* throws(Exception) */;
    static Matrix* add(Matrix* M1, Matrix* M2) /* throws(MatrixException) */;
    virtual Matrix* subtract(Matrix* M2) /* throws(MatrixException) */;
    static Matrix* subtract(Matrix* M1, Matrix* M2) /* throws(MatrixException) */;
    virtual Matrix* mult(double a) /* throws(MatrixException) */;
    static Matrix* transpose(Matrix* in) /* throws(MatrixException) */;
    static ::doubleArray* multVec(Matrix* A, ::doubleArray* x) /* throws(MatrixException) */;
    virtual void multSelf(double a);
    virtual Matrix* mult(Matrix* M2) /* throws(MatrixException) */;
    static Matrix* mult(Matrix* M1, Matrix* M2) /* throws(MatrixException) */;
    virtual void print() /* throws(MatrixException) */;
    static Matrix* inversMat3x3(Matrix* in) /* throws(MatrixException) */;
    static double det(double d1, double d2, double d3, double d4);

    // Generated
    Matrix(int32_t dimension);
    Matrix(int32_t rows, int32_t cols);
    Matrix(Matrix* M);
protected:
    Matrix(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
};
