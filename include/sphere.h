#include<mesh.h>
#include <GL/glew.h>
#include <Eigen/Core>
#include <vector3G.h>
#include <physics_entity.h>
#include <model.h>

#ifndef SPHERE
#define SPHERE
class Sphere  : public Model, public PhysicsEntity
{
    private:
	GLfloat m_radius;
    	Vector3Gf m_center; 

	void UVSphereMesh(const GLfloat radius, const Vector3Gf center, const GLuint numU, const GLuint numV, Mesh &mesh);    

    public:
        Sphere();    
    
        Sphere(GLfloat radius, Vector3Gf position, Vector3Gf velocity, GLfloat mass);

        void UpdateFromBuffers();

    
};
#endif
