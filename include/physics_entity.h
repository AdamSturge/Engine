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
        /**
            The position of this entity
        **/
    	Vector3Gf m_position;
        /**
            The next predicted position of this entity. 
        **/
        Vector3Gf m_next_position_buffer;    
        /**
            The velocity of this entity
        **/
        Vector3Gf m_velocity;
        /**
            The next predicted velocity of this entity
        **/
        Vector3Gf m_next_velocity_buffer;
        /**
            The mass of this entity
        **/
        GLfloat m_mass; // stores the mass of this game entity

        /**
            Creates an instance of PhysicsEntity centered at the origin, zero velocity, and unit mass
        **/
        PhysicsEntity();

        /** 
            Destructor for PhysicsEntity
        **/
        virtual ~PhysicsEntity(){};

    private :
        /**
            Called after UpdateFromBuffers. Allows subclasses to perform class specific actions when physical observables update
        **/
        virtual void OnUpdateFromBuffers() {};
    
};
#endif
