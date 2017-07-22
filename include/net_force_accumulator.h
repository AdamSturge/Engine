#ifndef NET_FORCE_ACCUMULATOR_H
#define NET_FORCE_ACCUMULATOR_H

#include <vector>
#include <memory>
#include <physics_entity.h>
#include <constant_force.h>
#include <gravity_force.h>

class NetForceAccumulator
{
    private:
        std::vector<ConstantForceGenerator> m_constant_forces;
        GravityForceGenerator m_gravity_force;
        bool gravity_on;

    public:

        /**
            Constructs a NetForceAccumulator
        **/
        NetForceAccumulator();

        /**
            Adds a new constant force to the simuluation
            @param a acceleration vector of the new constant force
        **/
        void AddConstantForce(Vector3Gf a);

        /**
            Enables/Disables universial gravitation between entities
            @param enable true to turn on gravtational attraction, false to turn off
        **/
        void EnableGravity(bool enable);

        /**
            Computes the net force acting on an entity in the sumulation via accumulation
            @param entity_ptrs list of all entities in the simulation
            @param entity_ptr entity whom the net force is acting on
            @param force vector that will be modified to contain the net force acting on the supplied entity
        **/
        void ComputeNetForce(
            const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs, 
            const std::shared_ptr<PhysicsEntity> entity_ptr, 
            Vector3Gf &force) const;

        /**
            Computes the net force jacobian for the supplied entity
            @param entity_ptrs list of all entities in the simulation
            @param entity_ptr entity whom the net force is acting on
            @param dFdx matrix that will be modified to contain the net force jacobian with respect to position
            @param dFdx matrix that will be modified to contain the net force jacobian with respect to velocity
        **/
        void ComputeNetForceJacobian(
            const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs, 
            const std::shared_ptr<PhysicsEntity> entity_ptr, 
            Eigen::Matrix<GLfloat,3,3> &dFdx, 
            Eigen::Matrix<GLfloat,3,3> &dFdv) const;


};

#endif
