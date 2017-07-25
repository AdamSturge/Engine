#ifndef SPRING_FORCE_H
#define SPRING_FORCE_H

#include <vector3G.h>
#include <memory>
#include <Eigen/Core>
#include <physics_entity.h>
#include <spring.h>

/**
    \brief Computes the spring force resulting from 2 entities being connected by a spring
**/
class SpringForceGenerator
{
    public : 
        /**
            Constructs a SpringForceGenerator
        **/
        SpringForceGenerator();

        /**
            Adds a spring force due to 2 entities being connected by a spring
            @param k stiffness coefficent of spring
            @param l0 rest length of spring
            @param entity1_ptr entity on one end of the spring. The force will be computed such that it acts on this entity.
            @param entity2_ptr entity on the other end of the spring. The negative of the computed force acts on this entity.
            @param F Force vector that will accumulate the constant force represented by this instance
        **/
        void AccumulateForce(
            const GLfloat k,
            const GLfloat l0,
            const std::shared_ptr<PhysicsEntity> entity1_ptr,
            const std::shared_ptr<PhysicsEntity> entity2_ptr,
            Vector3Gf &F) const;

        /**
            Adds the position jacobian
            @param spring spring connecting 2 entities
            @param dF Matrix that will accumulate the derivative of force with respect to position
        **/
        void AccumulatedFdx(const Spring spring, Eigen::Matrix<GLfloat,3,3> &dF) const;


};

#endif
