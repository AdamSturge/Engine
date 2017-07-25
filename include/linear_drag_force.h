#ifndef DRAG_FORCE_GENERATOR_H
#define DRAG_FORCE_GENERATOR_H

#include <Eigen/Core>
#include "vector3G.h"
#include <memory>
#include "physics_entity.h"

/**
    \brief Computes a simple linear drag force on the provided entity
**/
class LinearDragForceGenerator
{
    private:
        GLfloat m_beta; // drag coefficent

    public:

        /**
            Constructs a LinearDragForceGenerator
        **/
        LinearDragForceGenerator();

        /**
            Constructs a LinearDragForceGenerator with the chosen drag coefficient
            @param beta drag coefficent
        **/    
        LinearDragForceGenerator(GLfloat beta);

        /**
            @return the drag coefficent
        **/
        GLfloat GetDragCoeff();        

        /**
            Sets the drag coefficent
            @param beta drag coefficient
        **/
        void SetDragCoeff(GLfloat beta);

        /**
            Adds a drag force whose magnitude is proportional to the drag coeffient
            @param entity Entity whom the force will be applied against
            @param F Force vector that will accumulate the constant force represented by this instance
        **/
        void AccumulateForce(std::shared_ptr<PhysicsEntity> entity, Vector3Gf &F) const;

        /**
            Adds the velocity jacobian
            @param entity Entity whom the force is acting on
            @param dF Matrix that will accumulate the derivative of force with respect to velocity
        **/
        void AccumulatedFdv(const std::shared_ptr<PhysicsEntity> entity, Eigen::Matrix<GLfloat,3,3> &dF) const;


};

#endif
