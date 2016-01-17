/*utility-class
provides function to calculate orientation with the help of quaternionen
*/

#include "fg_geometry.hxx"
#include <math.h>


class Quat
{

public:
    //default constructor
    Quat(void);
    //constructor, initialize by the given values
    Quat(double x, double y, double z, double w)
    {
        m_x = x;
        m_y = y;
        m_z = z;
        m_w = w;
    }

    //default destructor
    ~Quat(void);

    //initialize with zeros
    Quat zeros(void)
    {
        m_x = 0;
        m_y = 0;
        m_z = 0;
        m_w = 0;
    }
    /// Create a quaternion from the angle axis representation where the angle
    /// is stored in the axis' length
    static Quat fromAngleAxis(const Point3D& axis);

    /// Return a quaternion from real and imaginary part
    static Quat fromRealImag(double r, Point3D& i);

    /// Return the conjugate quaternion
    static Quat conjugate(Quat q);

    /// write the euler angles into the references
    void getEulerRad(float& zRad, float& yRad, float& xRad) const;

    /// Return a quaternion from euler angles which describes the transformation from DIS-global to FG-local
    static Quat fromDISglobToFGlocByEulerRad(float& phi, float& theta, float& psi);

    /// Return a quaternion from euler angles which describes the transformation from DIS-global to DIS-local
    static Quat fromDISglobToDISlocByEulerRad(float& phi, float& theta, float& psi);

    /// Return a AngleAxis from Quat
    static Point3D getAngleAxis(Quat q);

    /// rotates a vector from DIS-local to FG-local
    static Point3D fromDISlocToFGloc(Point3D vector);


    /// Return a AngleAxis from EulerRad
    static Point3D fromEulerRadtoAngleAxis(float phi, float theta, float psi);

    ///Return Hamilton-Product   of trwo quaternions
    static Quat hamiltonProd(Quat q, Quat e );

    double getX();
    double getY();
    double getZ();
    double getW();

    //rotates a given vector with angleaxis
    static Point3D rotByangleaxis(Point3D vector, Point3D angleaxis);

private:
    void normalise();

    //x-part of the imaginary-part of the quaternion
    double m_x;
    //y-part of the imaginary-part of the quaternion
    double m_y;
    //z-part of the imaginary-part of the quaternion
    double m_z;
    //real part of the quaternion
    double m_w;


};
