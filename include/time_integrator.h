#include <Eigen/Core>
#include <GL/glew.h>
#include <vector3G.h>

#ifndef TIME_INTEGRATOR
#define TIME_INTEGRATOR
/**
    \brief An abstact base class for all grid based numerical ODE solvers for Newton's laws
**/
class TimeIntegrator
{
    protected:
        GLfloat m_dt;

    public:
         virtual ~TimeIntegrator(){};

        /**
            Solves Newton's equations of motion
            @param xi initial position of entity
            @param vi initial velocity of entity
            @param mass mass of entity 
            @param F force vector acting on the entity
            @param xf final position of entity. This will be updated with the new position for the next time step
            @param vf final velocity of entity. This will be updated with the new position for the next time step
        **/
         virtual void Solve(
            const Vector3Gf xi,
            const Vector3Gf vi, 
            const GLfloat mass,
            const Vector3Gf F,
            Vector3Gf &xf,
            Vector3Gf &vf) = 0;
};
#endif
