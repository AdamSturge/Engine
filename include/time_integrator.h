#include <Eigen/Core>
#include <GL/glew.h>
#include <vector3G.h>

#ifndef TIME_INTEGRATOR
#define TIME_INTEGRATOR
class TimeIntegrator
{
    protected:
        GLfloat m_dt;

    public:
         virtual ~TimeIntegrator(){};

         virtual void Solve(
            const Vector3Gf xi,
            const Vector3Gf vi, 
            const GLfloat mass,
            const Vector3Gf F,
            Vector3Gf &xf,
            Vector3Gf &vf) = 0;
};
#endif
