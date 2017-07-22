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

