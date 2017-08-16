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

        void GenerateMesh();

    public:
        RectangularPrism(GLuint length, GLuint width, GLuint height, Vector3Gf postion, Vector3Gf velocity, GLfloat mass, Material material);

        /**
            Loads the next position and velocity values from their respective buffers
        **/
        void OnUpdateFromBuffers();

};
#endif
