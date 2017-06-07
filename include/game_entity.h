#include <mesh.h>
#include <Eigen/Core>
#include <vector3G.h>

#ifndef GAME_ENTITY
#define GAME_ENTITY
class GameEntity{
   public:
        enum class ENTITY_TYPE {SPHERE_ENTITY};

        ENTITY_TYPE GetEntityType();

        Eigen::Matrix<GLfloat,4,4> GetModelMatrix();
        
        void SetModelMatrix(Eigen::Matrix<GLfloat,4,4> model);

        Mesh GetMesh();
        
	Vector3Gf GetPosition();

        void SetNextPosition(Vector3Gf x);

        Vector3Gf GetVelocity();

        void SetNextVelocity(Vector3Gf v);

        GLfloat  GetMass();

        void UpdateFromBuffers();

     protected:
        ENTITY_TYPE m_entity_type;

        Mesh m_mesh; 
    	Eigen::Matrix<GLfloat,4,4> m_model_matrix;  
        
        Vector3Gf m_position;
        Vector3Gf m_next_position_buffer; // Stores the next predicted position of this game entity
        
        Vector3Gf m_velocity;
        Vector3Gf m_next_velocity_buffer; // Stores the next predicted velocity of this game entity

        GLfloat m_mass; // stores the mass of this game entity

        GameEntity();
    
};
#endif
