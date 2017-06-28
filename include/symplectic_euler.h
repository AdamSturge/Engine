#include <time_integrator.h>
#include <Eigen/Core>
#include <vector3G.h>

#ifndef SYMPLECTIC_EULER_H
#define SYMPLECTIC_EULER_H
/**
    \brief Implementation of Symplectic Euler method for solving Newton's equations of motion
**/
class SymplecticEuler : public TimeIntegrator
{
    public :
        /**
            Constructs an instance of SymplecticEuler with a default grid size
        **/
        SymplecticEuler();

        /**
            Constructs an instance of SymplecticEuler with the provided grid size
            @param dt difference between two points on the grid
        **/
        SymplecticEuler(GLfloat dt);

    private:

        /**
            Solves Newton's equations of motion
            @param xi intial position of entity
            @param vi initial velocity of entity
            @param mass mass of entity
            @param F force vector acting on the entity
            @param xf final poisition of entity. This will be updated with the new position for the next time step
            @param vf final velocity of entity. This will be ipdated with the new velocity for the next time step
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

