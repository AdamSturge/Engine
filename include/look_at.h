#include <Eigen/Core>

//http://spointeau.blogspot.ca/2013/12/hello-i-am-looking-at-opengl-3.html

template<class T>
Eigen::Matrix<T,4,4> LookAt
( 
    Eigen::Matrix<T,3,1> const & eye, // camera viewport
    Eigen::Matrix<T,3,1> const & center, // where you are looking
    Eigen::Matrix<T,3,1> const & up // world up
)
{
    typedef Eigen::Matrix<T,4,4> Matrix4;
    typedef Eigen::Matrix<T,3,1> Vector3;

    Vector3 f = (center - eye).normalized();
    Vector3 u = up.normalized();
    Vector3 s = f.cross(u).normalized();
    u = s.cross(f);

    Matrix4 res;
    res <<  s.x(),s.y(),s.z(),-s.dot(eye),
            u.x(),u.y(),u.z(),-u.dot(eye),
            -f.x(),-f.y(),-f.z(),f.dot(eye),
            0,0,0,1;

    return res;
};
