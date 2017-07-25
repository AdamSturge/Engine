#ifndef NET_FORCE_ACCUMULATOR_H
#define NET_FORCE_ACCUMULATOR_H

#include <vector>
#include <memory>
#include <physics_entity.h>
#include <constant_force.h>
#include <gravity_force.h>
#include <linear_drag_force.h>
#include <unordered_map>
#include <spring.h>
#include <spring_force.h>

class NetForceAccumulator
{
    private:
        std::vector<ConstantForceGenerator> m_constant_forces;
        GravityForceGenerator m_gravity_force;
        bool gravity_on;
        LinearDragForceGenerator m_drag_force;
        bool drag_on;
        SpringForceGenerator m_spring_force;
        std::unordered_map<GLint, Spring> m_springs; // maps spring id to spring
        std::unordered_map<GLint,std::vector<GLint>> m_entity_spring_map; // maps physics id to springs it is a part of (by id)

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
            Enables/Disables velocity based drag
            @param enable true to turn on drag, false to turn off
        **/
        void EnableDrag(bool enable);

        /**
            Set the drag coefficent. Large values mean stronger drag
        **/
        void SetDragCoeff(GLfloat beta);

        /**
            Adds a spring to the force simulation
        **/
        void AddSpring(Spring spring);

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
            @param dFdv matrix that will be modified to contain the net force jacobian with respect to velocity
        **/
        void ComputeNetForceJacobian(
            const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs, 
            const std::shared_ptr<PhysicsEntity> entity_ptr, 
            Eigen::Matrix<GLfloat,3,3> &dFdx, 
            Eigen::Matrix<GLfloat,3,3> &dFdv) const;


};

#endif
