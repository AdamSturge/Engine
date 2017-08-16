#include <mesh.h>
#include <iostream>
#include <unordered_map>
#include <vector3G.h>
#include <Eigen/Dense>

Mesh::Mesh(){};

Mesh::Mesh(List3df vertices, List3di faces)
{
    // Note : Order is important!
    m_vertices = vertices;
    m_faces = faces;
    ComputeNormals();
    GenerateVAO();
    
}

List3df Mesh::GetVertices()
{
    return m_vertices;
}

List3di Mesh::GetFaces()
{
    return m_faces;
}

List3df Mesh::GetFaceNormals()
{
    return m_face_normals;
}

GLuint Mesh::GetNumEdges()
{
    return 3*m_faces.rows();
};

GLuint Mesh::GetVAO()
{
    return m_VAO;
}

void Mesh::GenerateVAO()
{
    glGenVertexArrays(1,&m_VAO);
 
    glGenBuffers(1,&m_VBO);

    glGenBuffers(1,&m_EBO);

    glBindVertexArray(m_VAO);

    GLuint n_V = m_vertices.rows();
    GLfloat vertices[6*n_V];
    for(int i=0; i < n_V; i++)
    {
        vertices[6*i]   = m_vertices(i,0);
        vertices[6*i+1] = m_vertices(i,1);
        vertices[6*i+2] = m_vertices(i,2);
        vertices[6*i+3] = m_vertex_normals(i,0);
        vertices[6*i+4] = m_vertex_normals(i,1);
        vertices[6*i+5] = m_vertex_normals(i,2);
    }

    GLuint n_F = m_faces.rows();
    GLint indices[3*n_F];
    Eigen::Map<List3di>( indices, m_faces.rows(), m_faces.cols() ) = m_faces;

    glBindBuffer(GL_ARRAY_BUFFER,m_VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // face normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); // unbind vertex array
};

void Mesh::CleanUp()
{
    glDeleteVertexArrays(1,&m_VAO);
    glDeleteBuffers(1,&m_VBO);
    glDeleteBuffers(1,&m_EBO);
}

void Mesh::ComputeNormals()
{
    int n_F = m_faces.rows();
    int n_V = m_vertices.rows();
    m_face_normals = List3df(n_F,3);
    m_vertex_normals = List3df(n_V,3);
    std::unordered_map<GLuint,Vector3Gf> vertex_normals;
    for(int i=0; i < n_F; ++i)
    {
        GLuint a = m_faces(i,0);
        GLuint b = m_faces(i,1);
        GLuint c = m_faces(i,2);

        Vector3Gf A = m_vertices.row(m_faces(i,0)); 
        Vector3Gf B = m_vertices.row(m_faces(i,1)); 
        Vector3Gf C = m_vertices.row(m_faces(i,2));

        Vector3Gf BA = B - A;
        Vector3Gf CA = C - A;

        Vector3Gf face_normal = BA.cross(CA);

        if(vertex_normals.find(a) == vertex_normals.end())
        {
            vertex_normals[a] = face_normal;
        }
        else
        {
            vertex_normals[a] += face_normal;
        }
        
        if(vertex_normals.find(b) == vertex_normals.end())
        {
            vertex_normals[b] = face_normal;
        }
        else
        {
            vertex_normals[b] += face_normal;
        }

        if(vertex_normals.find(c) == vertex_normals.end())
        {
            vertex_normals[c] = face_normal;
        }
        else
        {
            vertex_normals[c] += face_normal;
        }

        face_normal.normalize();

        m_face_normals.row(i) = face_normal.transpose();

    }

    for(auto iter = vertex_normals.begin(); iter != vertex_normals.end(); iter++)
    {
        Vector3Gf vertex_normal = iter->second;
        vertex_normal.normalize();
        m_vertex_normals.row(iter->first) = vertex_normal;
    }
}
