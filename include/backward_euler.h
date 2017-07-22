#ifndef BACKWARD_EULER_H
#define BACKWARD_EULER_H
#include "time_integrator.h"

/**
    \brief Implementation of Backward Euler method for solving Newton's Laws
**/
class BackwardEuler : public TimeIntegrator
{
    public:
        BackwardEuler();

        BackwardEuler(GLfloat dt);

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

        /**
            Computes the Jacobian of the update rule for use in Newton's Method
            @param mass mass of entity being simulated
            @param dFdx position force jacobian
            @param dFdx velocity force jacobian
            @param J matrix that will be modified to contain the update rule jacobian
        **/
        void ComputeJacobian(
                         const GLfloat mass, 
                         const Eigen::Matrix<GLfloat,3,3> dFdx,
                         const Eigen::Matrix<GLfloat,3,3> dFdv,
                         Eigen::Matrix<GLfloat,6,6> &J) const;       
};
#endif
