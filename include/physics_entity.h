#include <mesh.h>
#include <Eigen/Core>
#include <vector3G.h>

#ifndef PHYSICS_ENTITY
#define PHYSICS_ENTITY
class PhysicsEntity{
   public:
 enum class ENTITY_TYPE {SPHERE_ENTITY};

        ENTITY_TYPE GetEntityType();	

Vector3Gf GetPosition();

        void SetNextPosition(Vector3Gf x);

        Vector3Gf GetVelocity();

        void SetNextVelocity(Vector3Gf v);

        GLfloat  GetMass();

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
