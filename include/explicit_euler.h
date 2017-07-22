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
            Private implementation details for solver.
            @param net_force_accumulator accumulates the net force acting on entity_ptr
			@param entity_ptrs list of all the PhysicsEntities in the scene
            @param entity_ptr pointer to the entity being updated
        **/
        void Solve(
            const NetForceAccumulator& net_force_accumulator,
			const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr);

};
#endif

