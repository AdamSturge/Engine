#include<mesh.h>
#include <GL/glew.h>
#include <Eigen/Core>
#include <vector3G.h>
#include <physics_entity.h>
#include <model.h>

#ifndef SPHERE
#define SPHERE
/**
    \brief A sphere

    A Sphere is defined by a center and a radius. Sphere extends Model. As such is will be rendered to the screen
**/
class Sphere  : public Model
{
    private:
	GLfloat m_radius;
    	Vector3Gf m_center; 

	void UVSphereMesh(const GLfloat radius, const Vector3Gf center, const GLuint numU, const GLuint numV, Mesh &mesh);    

    public:
        /**
            Constructs a Sphere of radius 1.0, mass 1.0, centered at the origin
        **/
        Sphere();    
    
        /**
            Constructs a sphere
            @param radius radius of the Sphere
            @param position position of the Sphere (ie its center)
        **/
        Sphere(GLfloat radius, Vector3Gf position);

    
};
#endif
