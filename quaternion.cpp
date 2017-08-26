#include <quaternion.h>
Quaternion::Quaternion(){}

Quaternion::Quaternion(GLfloat real, Vector3Gf imag)
{
    r = real;
    im = imag;
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
    return Quaternion(r,-im);
}

Quaternion Quaternion::inv() const
{
    return (this->conjugate())/this->norm();
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
