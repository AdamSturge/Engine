#ifndef DRAG_FORCE_GENERATOR_H
#define DRAG_FORCE_GENERATOR_H

#include <Eigen/Core>
#include "vector3G.h"
#include <memory>
#include "physics_entity.h"

class DragForceGenerator
{
    private:
        GLfloat m_beta; // drag coefficent

    public:

        /**
            Constructs a DragForceGenerator
        **/
        DragForceGenerator();

        /**
            Constructs a DragForceGenerator with the chosen drag coefficient
            @param beta drag coefficent
        **/    
        DragForceGenerator(GLfloat beta);

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

};

#endif
