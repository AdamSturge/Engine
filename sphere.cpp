#include <sphere.h>
#include <iostream>

Sphere::Sphere() : Model(), PhysicsEntity()
{
    m_entity_type = PhysicsEntity::ENTITY_TYPE::SPHERE_ENTITY;
    m_radius = 1.0f;
    m_center = Vector3Gf(0.0f,0.0f,0.0f);
    UVSphereMesh(m_radius, Vector3Gf(0.0f,0.0f,0.0f), 20, 20, m_mesh);
};

Sphere::Sphere(GLfloat radius, Vector3Gf position, Vector3Gf velocity, GLfloat mass) : Model(), PhysicsEntity()
{
    m_entity_type = PhysicsEntity::ENTITY_TYPE::SPHERE_ENTITY;
       
    m_radius = radius;
    m_center = position;

    m_position = position;
    m_velocity = velocity;
    m_mass = mass; 

    m_model_matrix.col(3) << position(0), position(1), position(2), 1.0f; 
    UVSphereMesh(m_radius, Vector3Gf(0.0f,0.0f,0.0f), 20, 20, m_mesh); // model matrix handles translation of mesh so we use (0,0,0) as mesh center

};


void Sphere::UpdateFromBuffers()
{
    PhysicsEntity::UpdateFromBuffers();
    m_center = m_position;
    m_model_matrix.setIdentity();
    m_model_matrix.col(3)  << m_center(0), m_center(1), m_center(2), 1.0f; 
};

void Sphere::UVSphereMesh(const GLfloat radius, const Vector3Gf center, const GLuint numU, const GLuint numV, Mesh& mesh)
{
    GLfloat uStart = 0.0f;
    GLfloat vStart = 0.0f;
    GLfloat uEnd = 2*M_PI;
    GLfloat vEnd = M_PI;

    GLfloat uStep = (uEnd - uStart)/numU;
    GLfloat vStep = (vEnd - vStart)/numV;

    int eIndex = 0;

    std::vector<GLfloat> vertices;
    std::vector<std::pair<GLuint,GLuint>> edges;

    for(int i = 0; i < numU; i++)
    {
        GLfloat u = uStart + i*uStep;
        GLfloat un = (i+1 == numU) ? uEnd : (u + uStep);
        for(int j = 0; j < numV; j++)
        {
            GLfloat v = vStart + j*vStep;
            GLfloat vn = (j+1 == numV) ? vEnd : (v + vStep);

            Vector3Gf p0 = radius*Vector3Gf(cos(u)*sin(v),cos(v),sin(u)*sin(v)) - center; 
            Vector3Gf p1 = radius*Vector3Gf(cos(u)*sin(vn),cos(vn),sin(u)*sin(vn)) - center;
            Vector3Gf p2 = radius*Vector3Gf(cos(un)*sin(v),cos(v),sin(un)*sin(v)) - center; 
            Vector3Gf p3 = radius*Vector3Gf(cos(un)*sin(vn),cos(vn),sin(un)*sin(vn)) - center;

            vertices.push_back(p0(0)); vertices.push_back(p0(1)); vertices.push_back(p0(2));
            vertices.push_back(p1(0)); vertices.push_back(p1(1)); vertices.push_back(p1(2));
            vertices.push_back(p2(0)); vertices.push_back(p2(1)); vertices.push_back(p2(2));
            vertices.push_back(p3(0)); vertices.push_back(p3(1)); vertices.push_back(p3(2));
                   
            edges.push_back(std::pair<GLuint,GLuint>(eIndex+2,eIndex+0));
            edges.push_back(std::pair<GLuint,GLuint>(eIndex+1,eIndex+2));
            edges.push_back(std::pair<GLuint,GLuint>(eIndex+0,eIndex+1));

            edges.push_back(std::pair<GLuint,GLuint>(eIndex+1,eIndex+3));
            edges.push_back(std::pair<GLuint,GLuint>(eIndex+2,eIndex+1));
            edges.push_back(std::pair<GLuint,GLuint>(eIndex+3,eIndex+2));

            eIndex += 4;
        }
    }

    mesh = Mesh(vertices,edges);
};

