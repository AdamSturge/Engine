#include <mesh.h>
#include <iostream>

Mesh::Mesh(){};

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<std::pair<GLuint,GLuint>> edges)
{
    m_vertices = vertices;
    m_edges = edges;
    GenerateVAO();
}
/*
Mesh::~Mesh()
{
   // glDeleteVertexArrays(1,&m_VAO);
   // glDeleteBuffers(1,&m_VBO);
   // glDeleteBuffers(1,&m_EBO);

    std::cout << "Mesh deleted with VAO: " << m_VAO <<" and vertex count:" << m_vertices.size() << std::endl;
}

Mesh::Mesh(const Mesh& other)
{
    m_vertices = other.m_vertices;
    m_edges = other.m_edges;
    m_VAO = other.m_VAO;
    m_VBO = other.m_VBO;
    m_EBO = other.m_EBO;

}

Mesh::Mesh(Mesh&& other)
{
    m_vertices = other.m_vertices;
    m_edges = other.m_edges;
    m_VAO = other.m_VAO;
    m_VBO = other.m_VBO;
    m_EBO = other.m_EBO;

}

Mesh& Mesh::operator=(const Mesh& other)
{
    std::cout << "in copy assignment operator for mesh" << std::endl;
    Mesh tmp(other);
    *this = std::move(tmp);
    return *this;
}

Mesh& Mesh::operator=(Mesh&& other)
{
    std::cout << "in move assignment operator for mesh" << std::endl;
    m_vertices = other.m_vertices;
    m_edges = other.m_edges;
    m_VAO = other.m_VAO;
    m_VBO = other.m_VBO;
    m_EBO = other.m_EBO;
}
*/
std::vector<GLfloat> Mesh::GetVertices()
{
    return m_vertices;
}

std::vector<std::pair<GLuint,GLuint>> Mesh::GetEdges()
{
    return m_edges;
}

GLuint Mesh::GetNumEdges()
{
    return 2*m_edges.size();
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

    GLfloat vertices[m_vertices.size()];
    std::copy(m_vertices.begin(),m_vertices.end(),vertices);

    glBindBuffer(GL_ARRAY_BUFFER,m_VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
 
    GLuint indices[2*m_edges.size()];
    GLuint i = 0;
    for(std::pair<GLuint,GLuint> edge : m_edges)
    {
        indices[i] = edge.first;
        indices[i+1] = edge.second;
        i += 2;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); // unbind vertex array
};

void Mesh::CleanUp()
{
    glDeleteVertexArrays(1,&m_VAO);
    glDeleteBuffers(1,&m_VBO);
    glDeleteBuffers(1,&m_EBO);
}
