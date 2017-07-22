#ifndef TIME_INTEGRATOR_H
#define TIME_INTEGRATOR_H
#include <Eigen/Core>
#include <GL/glew.h>
#include <vector3G.h>
#include <net_force_accumulator.h>

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
            Public interface for all solvers. 
            Computes position and velocity updates by solving Newton's equations of motion.
            Updates entity_ptr buffers with next predicted position and velocity
            @param net_force_accumulator accumulates the net force acting on entity_ptr
			@param entity_ptrs list of all the PhysicsEntities in the scene
            @param entity_ptr pointer to the entity being updated
         **/
         void StepForward(
            const NetForceAccumulator& net_force_accumulator,
			const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr);

        /**
            Returns the current step size for the integrator
        **/
        GLfloat GetStepSize();

    private:
        /**
            Private implementation details for solver.
            @param net_force_accumulator accumulates the net force acting on entity_ptr
			@param entity_ptrs list of all the PhysicsEntities in the scene
            @param entity_ptr pointer to the entity being updated
        **/
         virtual void Solve(
            const NetForceAccumulator& net_force_accumulator,
			const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr) = 0;
};
#endif
