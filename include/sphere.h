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

    A Sphere is defined by a center and a radius. Sphere extends both Model and PhysicsEntity. As such is will be rendered to the screen and act under the influence of forces
**/
class Sphere  : public Model, public PhysicsEntity
{
    private:
	GLfloat m_radius;
    	Vector3Gf m_center; 

	void UVSphereMesh(const GLfloat radius, const GLuint numU, const GLuint numV, Mesh &mesh);    

    public:
        /**
            Constructs a Sphere of radius 1.0, mass 1.0, centered at the origin
        **/
        Sphere();    

        /**
            Deconstructs a sphere
        **/
        ~Sphere();            

        /**
            Constructs a sphere
            @param radius radius of the Sphere
            @param position position of the Sphere (ie its center)
            @param velocity velocity of the Sphere
            @param mass mass of the Sphere
            @param orientation orientation of the Sphere
            @param angular_velocity angular_velocity of the Sphere
            @param material material properties for the sphere
        **/
        Sphere(GLfloat radius, Vector3Gf position, Vector3Gf velocity, GLfloat mass, Quaternion orientation, Vector3Gf angular_velocity, Material material);

        /**
            Loads the next position and velocity values from their respective buffers
        **/
        void OnUpdateFromBuffers();

    
};
#endif
