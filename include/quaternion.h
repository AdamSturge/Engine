#ifndef QUATERNION_H
#define QUATERNION_H
#include <Eigen/Dense>
#include <vector3G.h>
#include <iostream>

struct Quaternion
{
	GLfloat r; // real part of quaternion
	Vector3Gf im; // imaginary part of quaternion

    Quaternion();

    Quaternion(GLfloat real, Vector3Gf imag);
    
    /**
     * @return the squared norm of the quaternion 
    * */
    GLfloat squaredNorm() const;

    /**
     *  @return the norm of the quaternion
     * */
    GLfloat norm() const;

    /**
     *  divides this quaternion by its norm
     * */
    void normalize();

    /**
     * @return the conjugate of this quaternion
     **/
    Quaternion conjugate() const;

    /**
     * @return the inverse of this quaternion
     **/
    Quaternion inv() const;

	Quaternion operator+(const Quaternion& q) const;

	Quaternion operator-(const Quaternion& q) const;

	Quaternion operator*(const Quaternion& q) const;

    friend Quaternion operator*(const Quaternion q, const GLfloat& s);
    
    friend Quaternion operator*(const GLfloat& s,const Quaternion q);

    Quaternion operator/(const GLfloat& s) const;

	Quaternion operator/(const Quaternion& q) const;

    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);  
};

#endif
