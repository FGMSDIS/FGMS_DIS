#include "Quat.h"
#include "fg_geometry.hxx"
#include "fg_geometry.cxx"
#include <math.h>
#include <limits.h>

Quat::Quat(void)
	{
	}

Quat::~Quat(void)
	{
	}

double Quat::getX()
	{
	return m_x;
	}

double Quat::getY()
	{
	return m_y;
	}
double Quat::getZ()
	{
	return m_z;
	}
double Quat::getW()
	{
	return m_w;
	}

/// Create a quaternion from the angle axis representation where the angle
/// is stored in the axis' length
Quat Quat::fromAngleAxis(const Point3D& axis)
	{
	//create Quaternion
	Quat q;
	Point3D vn(axis);
	vn.normalize();
	double sinHalfAngle = sin( (0.5 * axis.length() ) );

	q.m_w = cos( (0.5 * axis.length() ) );
	q.m_x = (vn[X] * sinHalfAngle);
	q.m_y = (vn[Y] * sinHalfAngle);
	q.m_z = (vn[Z] * sinHalfAngle);

	q.normalise();

	return q;
	}


/// write the euler angles into the references
void Quat::getEulerRad(float& psi,  float& theta, float& phi) const
	{
	
	double sqrQW = this->m_w * this->m_w;
	double sqrQX = this->m_x * this->m_x;
	double sqrQY = this->m_y * this->m_y;
	double sqrQZ = this->m_z * this->m_z;

    double num = 2*( this->m_y * this->m_z + this->m_w * this->m_x);
    double den = sqrQW - sqrQX - sqrQY + sqrQZ;
	double pol = (this->m_y * this->m_x) - (this->m_w * this->m_z);
	
	//compute phi
	if (pol > 0.5)
		phi = 0;
    else
		phi = atan2(num, den);

	//compute theta
    double tmp = -2*(this->m_x * this->m_z - this->m_w * this->m_y);
    if (tmp <= -1)
		theta = (0.5)*SG_PI;
    else if (1 <= tmp)
		theta = -(0.5)*SG_PI;
    else
		theta = asin(tmp);

	//compute psi
    num = 2*(this->m_x*this->m_y + this->m_w*this->m_z);
    den = sqrQW + sqrQX - sqrQY - sqrQZ;
	
	if (pol < -0.5 )
		psi = 0;
	else 
		{
      float tmppsi = atan2(num, den);
      if (tmppsi < 0) tmppsi += 2*SG_PI;
      psi = tmppsi;
		}
	
	}
/// Return a quaternion from euler angles
Quat Quat::fromDISglobToFGlocByEulerRad(float& phi, float& theta, float& psi)
  {
    Quat q;
    float zd2 = (0.5)*psi; float yd2 = (0.5)*theta; float xd2 = (0.5)*phi;

    float Szd2 = sin(zd2); float Syd2 = sin(yd2); float Sxd2 = sin(xd2);
    float Czd2 = cos(zd2); float Cyd2 = cos(yd2); float Cxd2 = cos(xd2);
	//hamilton product for Qzy=Qz*Qy
    float Cxd2Czd2 = Cxd2*Czd2; float Cxd2Szd2 = Cxd2*Szd2;
    float Sxd2Szd2 = Sxd2*Szd2; float Sxd2Czd2 = Sxd2*Czd2;
	//hamilton product for Qzy*Qx
    q.m_x = Sxd2Czd2*Cyd2 - Cxd2Szd2*Syd2;//inverted to transform from DIS-global to FG-local instead of DIS-local
    q.m_y = Cxd2Czd2*Syd2 + Sxd2Szd2*Cyd2;//same equation for either transformation (DIS-local / FG-local)
    q.m_z = Cxd2Szd2*Cyd2 - Sxd2Czd2*Syd2;//inverted to transform from DIS-global to FG-local instead of DIS-local
	q.m_w = Cxd2Czd2*Cyd2 + Sxd2Szd2*Syd2;//inverted to transform from DIS-global to FG-local instead of DIS-local
	q.normalise();
    return q;
  }
/// Return a quaternion from euler angles
Quat Quat::fromDISglobToDISlocByEulerRad(float& psi, float& theta, float& phi)
  {
    Quat q;

	Quat qPsi = Quat( 0.0, 0.0, sin(psi/2), cos(psi/2) );
	Quat qTheta = Quat( 0.0, sin(theta/2), 0.0, cos(theta/2) );
	Quat qPhi = Quat( sin(phi/2), 0.0, 0.0, cos(phi/2) );

	q = Quat::hamiltonProd(qPsi, qTheta);
	q = Quat::hamiltonProd(q, qPhi);

 //   float zd2 = (0.5)*psi; float yd2 = (0.5)*theta; float xd2 = (0.5)*phi;


 //   float Szd2 = sin(zd2); float Syd2 = sin(yd2); float Sxd2 = sin(xd2);
 //   float Czd2 = cos(zd2); float Cyd2 = cos(yd2); float Cxd2 = cos(xd2);
	////hamilton product for Qzy=Qz*Qy
 //   float Cxd2Czd2 = Cxd2*Czd2; float Cxd2Szd2 = Cxd2*Szd2;
 //   float Sxd2Szd2 = Sxd2*Szd2; float Sxd2Czd2 = Sxd2*Czd2;
	////hamilton product for Qzy*Qx
 //   q.m_x = -Sxd2Czd2*Cyd2 + Cxd2Szd2*Syd2;
 //   q.m_y = +Cxd2Czd2*Syd2 + Sxd2Szd2*Cyd2;
 //   q.m_z = -Cxd2Szd2*Cyd2 + Sxd2Czd2*Syd2;
	//q.m_w = -Cxd2Czd2*Cyd2 - Sxd2Szd2*Syd2;		  

	q.normalise();
    return q;
  }
Point3D Quat::fromDISlocToFGloc(Point3D dis)
	{
	Point3D fg;
	fg.SetX( dis.GetX() );
	fg.SetY( -dis.GetY() );
	fg.SetZ( -dis.GetZ() );
	return fg;
	}

Point3D Quat::getAngleAxis(Quat q){

	Point3D point;
	double angle;

	if (q.m_w > 1)							// if w>1 acos will produce errors
		q.normalise();
	angle = 2 * acos(q.m_w);

	double s = sqrt(1 - q.m_w * q.m_w);		// because q is normalised then w is less than 1, so term always positive
	
	if ( s < 0.001) {						// if s so close to zero then direction of axis not important

		point.SetX(q.m_x);
		point.SetX(q.m_x);
		point.SetX(q.m_x);
		}
	else {									// normalise axis

		point.SetX(q.m_x / s);
		point.SetY(q.m_y / s);
		point.SetZ(q.m_z / s);
		}

	point.normalize();
	point.SetX(point.GetX() * angle);
	point.SetY(point.GetY() * angle);
	point.SetZ(point.GetZ() * angle);


	
	return point;
	}

void Quat::normalise() {

	double n = sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);

	m_x /= n;
	m_y /= n;
	m_w /= n;
	m_z /= n;

	}


Point3D Quat::fromEulerRadtoAngleAxis(float phi, float theta, float psi){

	// All the angles are in radian
	Point3D point;

	float c1 = cos(theta / 2);
	float s1 = sin(theta / 2);
	float c2 = cos(phi / 2);
	float s2 = sin(phi / 2);
	float c3 = cos(psi / 2);
	float s3 = sin(psi / 2);

	float c1c2 = c1*c2; 
	float s1s2 = s1*s2;

	float w = c1c2 * c3 - s1s2 * s3;
    float z = c1 * s2 * c3 - s1 * c2 * s3;
    float y = s1 * c2 * c3 + c1 * s2 * s3;
    float x = c1c2 * s3 + s1s2 * c3;

	float angle = 2 * acos(w);
	float norm = x*x + y*y + z*z;

	if (norm < 0.001) {
		x = 1;
		y = z = 0;
		}
	else {
		norm = sqrt(norm);
		x /= norm;
		y /= norm;
		z /= norm;
		}
	point.SetX(x);
	point.SetY(y);
	point.SetZ(z);

	point.normalize();
	point.SetX(point.GetX() * angle);
	point.SetY(point.GetY() * angle);
	point.SetZ(point.GetZ() * angle);



	return point;
	}


Quat Quat::conjugate(Quat q)
	{
	Quat qConj;
	qConj.m_x = -q.m_x;
	qConj.m_y = -q.m_y;
	qConj.m_z = -q.m_z;
	qConj.m_w = q.m_w;
	qConj.normalise();
	return qConj;
	}

Quat Quat::hamiltonProd(Quat q, Quat e)
	{
	 Quat hamProd;
	 hamProd.m_w = q.m_w*e.m_w - q.m_x*e.m_x - q.m_y*e.m_y - q.m_z*e.m_z;
	 hamProd.m_x = q.m_w*e.m_x + q.m_x*e.m_w + q.m_y*e.m_z - q.m_z*e.m_y;
	 hamProd.m_y = q.m_w*e.m_y - q.m_x*e.m_z + q.m_y*e.m_w + q.m_z*e.m_x;
	 hamProd.m_z = q.m_w*e.m_z + q.m_x*e.m_y - q.m_y*e.m_x + q.m_z*e.m_w;
	 return hamProd;
	}

Point3D Quat::rotByangleaxis(Point3D vector, Point3D angleaxis)
	{
	//extract angle
	float angle = angleaxis.length() ;
	//extract rotation axis
	Point3D axis = angleaxis;
	axis.normalize();
	//vector for our return value
	Point3D	vector2;

	float x = vector[0] * cos(angle) + axis[0]* (axis[1]*vector[2]-axis[2]*vector[1]) * (1 - cos(angle)) + (vector[1]*axis[2]-vector[2]*axis[1]) * sin(angle);
	float y = vector[1] * cos(angle) + axis[1]* (axis[2]*vector[0]-axis[0]*vector[2]) * (1 - cos(angle)) + (vector[2]*axis[0]-vector[0]*axis[2]) * sin(angle);
	float z = vector[2] * cos(angle) + axis[2]* (axis[0]*vector[1]-axis[1]*vector[0]) * (1 - cos(angle)) + (vector[0]*axis[1]-vector[1]*axis[0]) * sin(angle);

	vector2.SetX(x);
	vector2.SetY(y);
	vector2.SetZ(z);

	return vector2;
	}