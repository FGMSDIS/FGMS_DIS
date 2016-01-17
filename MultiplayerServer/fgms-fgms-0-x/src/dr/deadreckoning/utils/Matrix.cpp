// Generated from /DR/src/deadreckoning/utils/Matrix.java
#include <deadreckoning/utils/Matrix.hpp>

#include <deadreckoning/utils/MatrixException.hpp>
#include <java/io/PrintStream.hpp>
#include <java/io/Serializable.hpp>
#include <java/lang/ArrayStoreException.hpp>
#include <java/lang/Cloneable.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
#include <java/lang/StringBuilder.hpp>
#include <java/lang/System.hpp>
#include <Array.hpp>
#include <SubArray.hpp>
#include <ObjectArray.hpp>

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

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

deadreckoning::utils::Matrix::Matrix(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

deadreckoning::utils::Matrix::Matrix(int32_t dimension) 
    : Matrix(*static_cast< ::default_init_tag* >(0))
{
    ctor(dimension);
}

deadreckoning::utils::Matrix::Matrix(int32_t rows, int32_t cols) 
    : Matrix(*static_cast< ::default_init_tag* >(0))
{
    ctor(rows,cols);
}

deadreckoning::utils::Matrix::Matrix(Matrix* M)  /* throws(MatrixException) */
    : Matrix(*static_cast< ::default_init_tag* >(0))
{
    ctor(M);
}

void deadreckoning::utils::Matrix::init()
{
    epsilon = 1.0E-9;
}

void deadreckoning::utils::Matrix::ctor(int32_t dimension)
{
    super::ctor();
    init();
    data = new ::doubleArrayArray(dimension);
    for (auto i = int32_t(0); i < dimension; i++) 
                for (auto j = int32_t(0); j < dimension; j++) 
                        (*(*data)[i])[j] = ((i == j) ? int32_t(1) : int32_t(0));


}

void deadreckoning::utils::Matrix::ctor(int32_t rows, int32_t cols)
{
    super::ctor();
    init();
    data = new ::doubleArrayArray(rows);
    for (auto i = int32_t(0); i < rows; i++) {
        for (auto j = int32_t(0); j < cols; j++) 
                        (*(*data)[i])[j] = 0;

    }
}

void deadreckoning::utils::Matrix::ctor(Matrix* M) /* throws(MatrixException) */
{
    super::ctor();
    init();
    data = new ::doubleArrayArray(npc(M)->rows());
    replace(M);
}

void deadreckoning::utils::Matrix::replace(Matrix* M) /* throws(MatrixException) */
{
    if(npc(M)->rows() != rows() || npc(M)->cols() != cols())
        throw new MatrixException(u"M dim not = this dim"_j);

    for (auto i = int32_t(0); i < npc(M)->rows(); i++) 
                for (auto j = int32_t(0); j < npc(M)->cols(); j++) 
                        setCell(i, j, npc(M)->cell(i, j));


}

int32_t deadreckoning::utils::Matrix::cols()
{
    return (npc(data)->length > 0) ? npc((*data)[int32_t(0)])->length : int32_t(0);
}

int32_t deadreckoning::utils::Matrix::rows()
{
    return npc(data)->length;
}

double deadreckoning::utils::Matrix::cell(int32_t i, int32_t j) /* throws(MatrixException) */
{
    if(rows() <= i || rows() < 0)
        throw new MatrixException(u"Bad Row index"_j);

    if(cols() <= j || cols() < 0)
        throw new MatrixException(u"Bad COL index"_j);

    return (*(*data)[i])[j];
}

void deadreckoning::utils::Matrix::setCell(int32_t i, int32_t j, double value) /* throws(MatrixException) */
{
    if(rows() <= i || rows() < 0)
        throw new MatrixException(u"Bad Row index"_j);

    if(cols() <= j || cols() < 0)
        throw new MatrixException(u"Bad COL index"_j);

    (*(*data)[i])[j] = value;
}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::add(Matrix* M2) /* throws(MatrixException) */
{
    if(rows() != npc(M2)->rows() || cols() != npc(M2)->cols())
        throw new MatrixException(u"ERROR NOT SAME SIZE MATRIXES!!!!"_j);

    auto result = new Matrix(rows(), cols());
    for (auto i = int32_t(0); i < rows(); i++) {
        for (auto j = int32_t(0); j < cols(); j++) 
                        npc(result)->setCell(i, j, cell(i, j) + npc(M2)->cell(i, j));

    }
    return result;
}

void deadreckoning::utils::Matrix::add(Matrix* r1, double a) /* throws(Exception) */
{
    clinit();
    for (auto i = int32_t(0); i < npc(r1)->rows(); i++) {
        for (auto j = int32_t(0); j < npc(r1)->cols(); j++) 
                        npc(r1)->setCell(i, j, npc(r1)->cell(i, j) + a);

    }
}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::add(Matrix* M1, Matrix* M2) /* throws(MatrixException) */
{
    clinit();
    if(npc(M1)->rows() != npc(M2)->rows() || npc(M1)->cols() != npc(M2)->cols())
        throw new MatrixException(u"not equal dim matrixes"_j);

    return npc(M1)->add(M2);
}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::subtract(Matrix* M2) /* throws(MatrixException) */
{
    if(rows() != npc(M2)->rows() || cols() != npc(M2)->cols())
        throw new MatrixException(u"ERROR NOT SAME SIZE MATRIXES!!!!"_j);

    auto result = new Matrix(rows(), cols());
    for (auto i = int32_t(0); i < rows(); i++) 
                for (auto j = int32_t(0); j < cols(); j++) 
                        npc(result)->setCell(i, j, cell(i, j) - npc(M2)->cell(i, j));


    return result;
}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::subtract(Matrix* M1, Matrix* M2) /* throws(MatrixException) */
{
    clinit();
    if(npc(M1)->rows() != npc(M2)->rows() || npc(M1)->cols() != npc(M2)->cols())
        throw new MatrixException(u"not equal dim matrixes"_j);

    return npc(M1)->subtract(M2);
}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::mult(double a) /* throws(MatrixException) */
{
    auto result = new Matrix(rows(), cols());
    npc(result)->replace(this);
    npc(result)->multSelf(a);
    return result;
}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::transpose(Matrix* in) /* throws(MatrixException) */
{
    clinit();
    if(npc(in)->rows() < 1 || npc(in)->cols() < 1)
        throw new MatrixException(u"not a valid sized matrix one of the dim < 1"_j);

    auto r = npc(in)->rows();
    auto c = npc(in)->cols();
    auto trans = new Matrix(c, r);
    for (auto i = int32_t(0); i < r; i++) 
                for (auto j = int32_t(0); j < c; j++) 
                        npc(trans)->setCell(j, i, npc(in)->cell(i, j));


    return trans;
}

doubleArray* deadreckoning::utils::Matrix::multVec(Matrix* A, ::doubleArray* x) /* throws(MatrixException) */
{
    clinit();
    if(npc(A)->cols() != npc(x)->length)
        throw new MatrixException(u"Matrix and Vector not compatable sizes in multVec()"_j);

    auto rslt = new ::doubleArray(npc(x)->length);
    double buff = int32_t(0);
    for (auto i = int32_t(0); i < npc(A)->rows(); i++) {
        buff = 0;
        for (auto j = int32_t(0); j < npc(A)->cols(); j++) {
            buff += npc(A)->cell(i, j) * (*x)[j];
        }
        (*rslt)[i] = buff;
    }
    return rslt;
}

void deadreckoning::utils::Matrix::multSelf(double a)
{
    for (auto i = int32_t(0); i < rows(); i++) 
                for (auto j = int32_t(0); j < cols(); j++) 
                        (*(*data)[i])[j] *= a;


}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::mult(Matrix* M2) /* throws(MatrixException) */
{
    if(cols() != npc(M2)->rows())
        throw new MatrixException(::java::lang::StringBuilder().append(u"Wrong size matrix to multiply to this\n"_j)->append(u"this.cols must equal M2.rows"_j)->toString());

    auto result = new Matrix(rows(), npc(M2)->cols());
    double tmp = int32_t(0), tmp2 = int32_t(0), sum = int32_t(0);
    for (auto i = int32_t(0); i < npc(result)->rows(); i++) {
        for (auto j = int32_t(0); j < npc(result)->cols(); j++) {
            for (auto k = int32_t(0); k < npc(result)->cols(); k++) {
                tmp += cell(i, k) * npc(M2)->cell(k, j);
            }
            npc(result)->setCell(i, j, tmp);
            tmp = 0;
        }
    }
    return result;
}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::mult(Matrix* M1, Matrix* M2) /* throws(MatrixException) */
{
    clinit();
    return npc(M1)->mult(M2);
}

void deadreckoning::utils::Matrix::print() /* throws(MatrixException) */
{
    ::java::lang::String* ln;
    for (auto j = int32_t(0); j < rows(); j++) {
        ln = u""_j;
        for (auto i = int32_t(0); i < cols(); i++) 
                        ln = ::java::lang::StringBuilder(ln).append(::java::lang::StringBuilder().append(cell(j, i))->append(u"\t"_j)->toString())->toString();

        npc(::java::lang::System::out())->println(ln);
    }
}

deadreckoning::utils::Matrix* deadreckoning::utils::Matrix::inversMat3x3(Matrix* in) /* throws(MatrixException) */
{
    clinit();
    if(npc(in)->rows() != 3 || npc(in)->cols() != 3)
        throw new MatrixException(u"not a 3 x 3 matrix....Must be a 3x3"_j);

    auto a = npc(in)->cell(0, 0);
    auto b = npc(in)->cell(0, 1);
    auto c = npc(in)->cell(0, 2);
    auto d = npc(in)->cell(1, 0);
    auto e = npc(in)->cell(1, 1);
    auto f = npc(in)->cell(1, 2);
    auto g = npc(in)->cell(2, 0);
    auto h = npc(in)->cell(2, 1);
    auto i = npc(in)->cell(2, 2);
    auto DETinv = int32_t(1) / ((a * det(e, f, h, i) - d * det(b, c, h, i)) + g * det(b, c, e, f));
    auto inv = new Matrix(int32_t(3));
    npc(inv)->setCell(0, 0, det(e, f, h, i) * DETinv);
    npc(inv)->setCell(0, 1, det(c, b, i, h) * DETinv);
    npc(inv)->setCell(0, 2, det(b, c, e, f) * DETinv);
    npc(inv)->setCell(1, 0, det(f, d, i, g) * DETinv);
    npc(inv)->setCell(1, 1, det(a, c, g, i) * DETinv);
    npc(inv)->setCell(1, 2, det(c, a, f, d) * DETinv);
    npc(inv)->setCell(2, 0, det(d, e, g, h) * DETinv);
    npc(inv)->setCell(2, 1, det(b, a, h, g) * DETinv);
    npc(inv)->setCell(2, 2, det(a, b, d, e) * DETinv);
    return inv;
}

double deadreckoning::utils::Matrix::det(double d1, double d2, double d3, double d4)
{
    clinit();
    return d1 * d4 - d3 * d2;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* deadreckoning::utils::Matrix::class_()
{
    static ::java::lang::Class* c = ::class_(u"deadreckoning.utils.Matrix", 26);
    return c;
}

java::lang::Class* deadreckoning::utils::Matrix::getClass0()
{
    return class_();
}

