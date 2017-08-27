#include <mesh.h>
#include <Eigen/Core>
#include <vector3G.h>
#include <atomic>
#include <quaternion.h>

#ifndef PHYSICS_ENTITY
#define PHYSICS_ENTITY
/**
    \brief An entity subject to the laws of physics

    PhysicsEntity is a base class for all objects in a scene that respond to forces and other physical phenomenon  
**/
class PhysicsEntity{
   public:
        /**
            Returns the unique id for this entity
        **/
        GLint GetId() const;
    
        /**
            @return Spatial position for this entity
        **/
        Vector3Gf GetPosition();

        /**
            Sets the position for this entity. If possible use SetNextPosition instead
            @param x Next position for this entity
        **/
        void SetPosition(Vector3Gf x);

        /**
            Sets the next position buffer for this entity. This <b>DOES NOT</b> update the position until UpdateFromBuffers() is called.
            @param x new position for this entity
        **/
        void SetNextPosition(Vector3Gf x);
        
        /**
            @return position for next time step
        **/
        Vector3Gf GetNextPosition();

        /**
            @return Spatial velocity for this entity
        **/
        Vector3Gf GetVelocity();
        
        /**
            Sets the velocity for this entity. If possible use SetNextPosition instead
            @param v new velocity for this entity
        **/
        void SetVelocity(Vector3Gf v);
        
        /**
            Sets the next velocity buffer for the entity. This <b>DOES NOT</b> update the velocity until UpdateFromBuffers() is called.
            @param v Next velocity for this entity
        **/
        void SetNextVelocity(Vector3Gf v);

        /**
            @return velocity for next time step
        **/
        Vector3Gf GetNextVelocity();
        
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
            Unique id for this entity in world coordinates
        **/
        GLuint m_id;
        /**
            The position of this entity in word coordinates
        **/
    	Vector3Gf m_position;
        /**
            The next predicted position of this entity in world coordinates. 
        **/
        Vector3Gf m_next_position_buffer;    
        /**
            The velocity of this entity in world coordinates
        **/
        Vector3Gf m_velocity;
        /**
            The next predicted velocity of this entity in world coordiantes
        **/
        Vector3Gf m_next_velocity_buffer;
        /**
            The mass of this entity
        **/
        GLfloat m_mass;

        /**
         * The orientation of this entity 
         * */
        Quaternion m_orientation;

        /**
            Creates an instance of PhysicsEntity centered at the origin, zero velocity, and unit mass
        **/
        PhysicsEntity();

        /**
            Creates an instance of PhysicsEntity centered at the provided position with the provided velocity and mass
            @param position - position of center of mass in world coordinates
            @param velocity - velocity of the entity in world coordinates
            @param mass - mass of the entity
            @param orientation - orientation of the entity 
        **/
        PhysicsEntity(Vector3Gf position, Vector3Gf velocity, GLfloat mass, Quaternion orientation);

        /** 
            Destructor for PhysicsEntity
        **/
        virtual ~PhysicsEntity(){};

    private :
        static std::atomic<GLint> next_id;

        /**
            Called after UpdateFromBuffers. Allows subclasses to perform class specific actions when physical observables update
        **/
        virtual void OnUpdateFromBuffers() {};
    
};
#endif
