#include <quaternion.h>
#include <assert.h>
Quaternion::Quaternion(){}

Quaternion::Quaternion(GLfloat angle, Vector3Gf axis)
{
    GLfloat l2 = axis.squaredNorm();
    if(l2 != 1.0f)
    {
        axis = axis/sqrt(l2);
    }
    r = cos(angle/2.0f);
    im = sin(angle/2.0f)*axis;
}

GLfloat Quaternion::squaredNorm() const
{
    return r*r + im.squaredNorm();
}

GLfloat Quaternion::norm() const
{
    return sqrt(squaredNorm());
}

void Quaternion::normalize()
{
    (*this)/this->norm();
}

Quaternion Quaternion::conjugate() const
{
    Quaternion q3;
    q3.r = r;
    q3.im = -im;
    return q3;
}

Quaternion Quaternion::inv() const
{
    return (this->conjugate())/this->norm();
}

Eigen::Matrix<GLfloat,3,3> Quaternion::toRotationMatrix()
{
    Eigen::Matrix<GLfloat,3,3> R(3,3);
    GLfloat s = 1.0f/this->squaredNorm();
    R << 1 - 2*s*(im(1)*im(1) + im(2)*im(2)), 2*s*(im(0)*im(1) - im(2)*r),         2*s*(im(0)*im(2) + im(1)*r), 
         2*s*(im(0)*im(1) + im(2)*r),        1 - 2*s*(im(0)*im(0) + im(2)*im(2)), 2*s*(im(1)*im(2) - im(0)*r), 
         2*s*(im(0)*im(2) - im(1)*r),        2*s*(im(1)*im(2) + im(0)*r),         1-2*s*(im(0)*im(0) + im(1)*im(1));

    return R;
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
    Quaternion q3;
    q3.r = r + q.r;
    q3.im = im + q.im;
    return q3;
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
    Quaternion q3;
    q3.r = r - q.r;
    q3.im = im - q.im;
    return q3;
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
    Quaternion q3;
    q3.r = r*q.r - im.dot(q.im);
    q3.im = r*q.im + q.r*im + im.cross(q.im);
    return q3;
}

Quaternion operator*(const Quaternion q, const GLfloat& s)
{
    Quaternion q3;
    q3.r = s*q.r;
    q3.im = s*q.im;
    return q3;
}

Quaternion operator*(const GLfloat& s,const Quaternion q)
{
    return q*s;
}

Quaternion Quaternion::operator/(const GLfloat& s) const
{
    Quaternion q3;
    q3.r = r/s;
    q3.im = im/s;
    return q3;
}

Quaternion Quaternion::operator/(const Quaternion& q) const
{
    return (*this)*q.inv();
}

std::ostream& operator<<(std::ostream& os, const Quaternion& q)
{
        os << "(" << q.r << " " << q.im.transpose() << ")";
        return os;
}
