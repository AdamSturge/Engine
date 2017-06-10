#include <time_integrator.h>
#include <Eigen/Core>
#include <vector3G.h>

#ifndef EXPLICIT_EULER
#define EXPLICIT_EULER
/**
    \brief Implementation of Explicit Euler method for solving Newton's equations of motion
**/
class ExplicitEuler : public TimeIntegrator
{
    public :
        /**
            Constructs an instance of ExlplictEuler with a default grid size
        **/
        ExplicitEuler();

        /**
            Constructs an instance of ExplicitEuler with the provided grid size
            @param dt difference between two points on the grid
        **/
        ExplicitEuler(GLfloat dt);

        /**
            Solves Newton's equations of motion
            @param xi intial position of entity
            @param vi initial velocity of entity
            @param mass mass of entity
            @param xf Final poisition of entity. This will be updated with the new position for the next grid point
            @param vf Final velocity of entity. This will be ipdated with the new velocity for the next grid point
        **/
        void Solve(
            const Vector3Gf xi,
            const Vector3Gf vi,
            const GLfloat mass,
            const Vector3Gf F,
             Vector3Gf &xf,
             Vector3Gf &vf);

};
#endif

