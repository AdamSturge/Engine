#ifndef EXPLICIT_EULER
#define EXPLICIT_EULER

#include <time_integrator.h>
#include <Eigen/Core>
#include <vector3G.h>

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

