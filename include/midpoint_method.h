#ifndef MIDPOINT_METHOD_H
#define MIDPOINT_METHOD_H
#include "time_integrator.h"
#include "backward_euler.h"
#include "explicit_euler.h"
/**
    \brief Implementation of Midpoint method for solving Newton's Laws
**/
class MidpointMethod : public TimeIntegrator
{
    public:
        /**
            Constucts a MidpointMethod with the default time step
        **/
        MidpointMethod();

        /**
            Constructs a MidpointMethod with the provided timestep
            @param dt time step
            @param threshold if successive iterations are less than threshold different in norm then halt
            @param max_iter maximum number of iterations to run
        **/
        MidpointMethod(GLfloat dt, GLfloat threshold,GLuint max_iter);

    private:
        BackwardEuler m_backward_euler;
        
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
