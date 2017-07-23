#include <physics_entity.h>
#include <memory>
#include <vector3G.h>

#ifndef GRAVITY_FORCE_H
#define GRAVITY_FORCE_H

class GravityForceGenerator
{
    private :
        GLfloat m_G = 6.673e-11; // Universal gravitational constant 
    
    public :
        /**
            Builds a GravityForceGenerator
        **/
        GravityForceGenerator();

        /**
            Adds a constant force determined by the mass of the provided entity and the stored acceleration vector
            @param e1 Entity whom the force is acting on
            @param e2 Entity which is gravitationally interacting with e1
            @param F Force vector that will accumulate the constant force represented by this instance
        **/
        void AccumulateForce(const std::shared_ptr<PhysicsEntity> e1, const std::shared_ptr<PhysicsEntity> e2, Vector3Gf &F) const;

        /**
            Adds the position jacobian
            @param e1 Entity whom the force is acting on
            @param e2 Entity which is gravitationally interacting with e1
            @param dF Matrix that will accumulate the derivative of force with respect to position
        **/
        void AccumulatedFdx(const std::shared_ptr<PhysicsEntity> e1, const std::shared_ptr<PhysicsEntity> e2, Eigen::Matrix<GLfloat,3,3> &dF) const;

};

#endif
