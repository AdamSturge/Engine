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
            Solves Newton's equations of motion.
            Updates entity_ptr buffers with next predicted position and velocity
            @param scene scene containing entities to be integrated forward
            @param entity_ptr pointer to entity to be integrated forward
        **/
       void Solve(
            const Scene& scene,
            const std::shared_ptr<PhysicsEntity> entity_ptr);

};
#endif

