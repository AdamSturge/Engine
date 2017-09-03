#include <sphere.h>
#include <iostream>

Sphere::Sphere() : Model(), PhysicsEntity()
{
    m_radius = 1.0f;
    m_center = Vector3Gf(0.0f,0.0f,0.0f);
    UVSphereMesh(m_radius, 20, 20, m_mesh);
};

Sphere::~Sphere(){};

Sphere::Sphere(GLfloat radius, Vector3Gf position, Vector3Gf velocity, GLfloat mass, Quaternion orientation, Vector3Gf angular_velocity, Material material) : Model(), PhysicsEntity(position,velocity,mass,orientation, angular_velocity)
{      
    m_radius = radius;
    m_center = position;

    m_model_matrix.col(3) << position(0), position(1), position(2), 1.0f; 
    m_model_matrix.block(0,0,3,3) = orientation.toRotationMatrix();
    UVSphereMesh(m_radius, 20, 20, m_mesh); // model matrix handles translation of mesh so we use (0,0,0) as mesh center

    m_material = material;
};


void Sphere::OnUpdateFromBuffers()
{
    m_center = m_position;
    Eigen::Matrix<GLfloat,4,4> M(4,4);
    M.col(3)  << m_position(0), m_position(1), m_position(2), 1.0f;
    M.block(0,0,3,3) = m_orientation.toRotationMatrix();
    SetModelMatrix(M);   m_model_matrix.setIdentity();
};

void Sphere::UVSphereMesh(const GLfloat radius, const GLuint numU, const GLuint numV, Mesh& mesh)
{  
    GLfloat uStart = 0.0f;
    GLfloat vStart = 0.0f;
    GLfloat uEnd = 2*M_PI;
    GLfloat vEnd = M_PI;

    GLfloat uStep = (uEnd - uStart)/numU;
    GLfloat vStep = (vEnd - vStart)/numV;

    List3df vertices(numU*numV*4,3);
    List3di faces(numU*numV*2,3);

    int vIndex = -1;
    int fIndex = -1;
    int eIndex = 0;
    for(int i = 0; i < numU; i++)
    {
        GLfloat u = uStart + i*uStep;
        GLfloat un = (i+1 == numU) ? uEnd : (u + uStep);
        for(int j = 0; j < numV; j++)
        {
            GLfloat v = vStart + j*vStep;
            GLfloat vn = (j+1 == numV) ? vEnd : (v + vStep);

            Vector3Gf p0 = radius*Vector3Gf(cos(u)*sin(v),cos(v),sin(u)*sin(v)); 
            Vector3Gf p1 = radius*Vector3Gf(cos(u)*sin(vn),cos(vn),sin(u)*sin(vn));
            Vector3Gf p2 = radius*Vector3Gf(cos(un)*sin(v),cos(v),sin(un)*sin(v)); 
            Vector3Gf p3 = radius*Vector3Gf(cos(un)*sin(vn),cos(vn),sin(un)*sin(vn));

            vertices.row(++vIndex) = p0;
            vertices.row(++vIndex) = p1;
            vertices.row(++vIndex) = p2;
            vertices.row(++vIndex) = p3;

            fIndex++;
            
            faces(fIndex,0) = eIndex+0;
            faces(fIndex,1) = eIndex+2;
            faces(fIndex,2) = eIndex+1;

            fIndex++;		
            
            faces(fIndex,0) = eIndex+2;
            faces(fIndex,1) = eIndex+3;
            faces(fIndex,2) = eIndex+1;

            eIndex += 4;

        }
    }

    mesh = Mesh(vertices,faces);
};

