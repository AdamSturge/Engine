 #include "Eigen/Core"

template<class T>
Eigen::Matrix<T,4,4> perspective
(
    GLfloat fovy,
    GLfloat aspect,
    GLfloat zNear,
    GLfloat zFar
)
{
    assert(aspect > 0);
    assert(zFar > zNear);

    GLfloat radf = (M_PI/180.0)*fovy;

    GLfloat tanHalfFovy = tan(radf / 2.0);
    Eigen::Matrix<T,4,4> res = Eigen::Matrix<T,4,4>::Zero();
    res(0,0) = 1.0 / (aspect * tanHalfFovy);
    res(1,1) = 1.0 / (tanHalfFovy);
    res(2,2) = - (zFar + zNear) / (zFar - zNear);
    res(3,2) = - 1.0;
    res(2,3) = - (2.0 * zFar * zNear) / (zFar - zNear);
    return res;
}
