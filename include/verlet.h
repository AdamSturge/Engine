#include <time_integrator.h>

#ifndef VERLET_H
#define VERLET_H

/**
    \brief Implementation of velocity Verlet method for solving Newton's Laws
**/
class Verlet : public TimeIntegrator{

    public :
        /**
            Constructs an instance of Verlet with a default grid size
        **/
        Verlet();

        /**
            Constructs an instance of Verlet with the provided grid size
            @param dt difference between two points on the grid
        **/
        Verlet(GLfloat dt);

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
