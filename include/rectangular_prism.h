#ifndef RECTANGULAR_PRISM_H
#define RECTANGULAR_PRISM_h
#include <model.h>
#include <physics_entity.h>
#include <vector3G.h>
#include <material.h>

class RectangularPrism : public Model, public PhysicsEntity
{
    private:
        GLuint m_length;
        GLuint m_width;
        GLuint m_height;

        /**
         * Builds a mesh representing a Rectangular Prism
         * */
        void GenerateMesh();

    public:
        /**                                                                                    
         * Constructs a Rectangular Prism                                                                
         * @param length x dimension of the Rectangular Prism
         * @param width y dimension of the Rectangular Prism
         * @param height z dimension of the Rectangular Prism
         * @param position position of the Rectangular Prism                             
         * @param velocity velocity of the Rectangular Prism                                            
         * @param mass mass of the Rectangular Prism                                             
         * @param orientation orientation of the Rectangular Prism
         * @param angular_velocity angular velocity of the Rectangular Prism                                 
         * @param material material properties for the Rectangular Prism
         ***/ 
        RectangularPrism(GLuint length, GLuint width, GLuint height, Vector3Gf postion, Vector3Gf velocity, GLfloat mass, Quaternion orientation, Vector3Gf angular_velocity, Material material);

    protected:
        /**
            Loads the next position and velocity values from their respective buffers
        **/
        void OnUpdateFromBuffers();

	/**
	 * Calls base class versions of this function for Model and PhysicsEntity
	 */
	void OnModelMatrixUpdate();
};
#endif
