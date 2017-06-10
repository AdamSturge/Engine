#include <mesh.h>
#include <Eigen/Core>
#include <vector3G.h>

#ifndef PHYSICS_ENTITY
#define PHYSICS_ENTITY
/**
    \brief An entity subject to the laws of physics

    PhysicsEntity is a base class for all objects in a scene that respond to forces and other physical phenomenon  
**/
class PhysicsEntity{
   public:
        /**
            Enum representing the different kinds of physical entities there can be. Used in casting operations
        **/
        enum class ENTITY_TYPE {SPHERE_ENTITY};

        /**
            @return Entity type for this instance
        **/
        ENTITY_TYPE GetEntityType();	

        /**
            @return Spatial position for this entity
        **/
        Vector3Gf GetPosition();

        /**
            Sets the next position buffer for this entity. This <b>DOES NOT</b> update the position until UpdateFromBuffers() is called.
            @param x Next position for this entity
        **/
        void SetNextPosition(Vector3Gf x);

        /**
            @return Spatial velocity for this entity
        **/
        Vector3Gf GetVelocity();

        /**
            Sets the next velocity buffer for the entity. This <b>DOES NOT</b> update the velocity until UpdateFromBuffers() is called.
            @param v Next velocity for this entity
        **/
        void SetNextVelocity(Vector3Gf v);

        /**
            @return Mass of this entity
        **/
        GLfloat GetMass();

        /**
            Updates internal state from buffers. This will load the next position and velocity from their corresponding buffers
        **/
        void UpdateFromBuffers();

     protected:     
        ENTITY_TYPE m_entity_type;         

    	Vector3Gf m_position;
        Vector3Gf m_next_position_buffer; // Stores the next predicted position of this game entity
        
        Vector3Gf m_velocity;
        Vector3Gf m_next_velocity_buffer; // Stores the next predicted velocity of this game entity

        GLfloat m_mass; // stores the mass of this game entity

        PhysicsEntity();
    
};
#endif
