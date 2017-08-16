#include <rectangular_prism.h>
#include <iostream>
RectangularPrism::RectangularPrism(GLuint length, GLuint width, GLuint height, Vector3Gf position, Vector3Gf velocity, GLfloat mass, Material material) : Model(), PhysicsEntity(position,velocity,mass)
{
    m_length = length; 
    m_width  = width; 
    m_height = height; 

    m_model_matrix.col(3) << position(0), position(1), position(2), 1.0f; 
    GenerateMesh();

    m_material = material;
}

void RectangularPrism::GenerateMesh()
{
    List3df vertices(8,3);
    List3di faces(12,3);

    GLfloat l = (GLfloat)m_length/2.0f;
    GLfloat w = (GLfloat)m_width/2.0f;
    GLfloat h = (GLfloat)m_height/2.0f;

    // front face
    vertices.row(0) = Vector3Gf(-l,-w,h); // bottom left
    vertices.row(1) = Vector3Gf(-l, w,h); // top left
    vertices.row(2) = Vector3Gf( l,-w,h); // bottom right
    vertices.row(3) = Vector3Gf( l, w,h); // top right

    // back face
    vertices.row(4) = Vector3Gf(-l,-w,-h); // bottom left
    vertices.row(5) = Vector3Gf(-l, w,-h); // top left
    vertices.row(6) = Vector3Gf( l,-w,-h); // bottom right
    vertices.row(7) = Vector3Gf( l, w,-h); // top right

    // front face
    faces.row(0) = Vector3Gi(0,2,1);
    faces.row(1) = Vector3Gi(2,3,1);
   
    // back face
    faces.row(2) = Vector3Gi(6,4,7);
    faces.row(3) = Vector3Gi(4,5,7);

    // left face
    faces.row(4) = Vector3Gi(4,0,5); 
    faces.row(5) = Vector3Gi(0,1,5);

    // right face
    faces.row(6) = Vector3Gi(2,6,3);
    faces.row(7) = Vector3Gi(6,7,3);

    // bottom face
    faces.row(8) = Vector3Gi(4,2,0);
    faces.row(9) = Vector3Gi(4,6,2);

    // top face
    faces.row(10) = Vector3Gi(3,7,1);
    faces.row(11) = Vector3Gi(7,5,1);

    m_mesh = Mesh(vertices,faces);
}

void RectangularPrism::OnUpdateFromBuffers()
{
    m_model_matrix.setIdentity();
    m_model_matrix.col(3)  << m_position(0), m_position(1), m_position(2), 1.0f;
};

