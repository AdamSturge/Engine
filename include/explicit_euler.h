#include <time_integrator.h>
#include <Eigen/Core>
#include <vector3G.h>

#ifndef EXPLICIT_EULER
#define EXPLICIT_EULER
class ExplicitEuler : public TimeIntegrator
{
    public :
        ExplicitEuler();

        ExplicitEuler(GLfloat dt);

        void Solve(
            const Vector3Gf xi,
            const Vector3Gf vi,
            const GLfloat mass,
            const Vector3Gf F,
             Vector3Gf &xf,
             Vector3Gf &vf);

};
#endif

