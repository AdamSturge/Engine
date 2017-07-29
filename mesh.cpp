#include <mesh.h>
#include <iostream>

Mesh::Mesh(){};

Mesh::Mesh(List3df vertices, List3di faces, List3df normals)
{
    m_vertices = vertices;
    m_faces = faces;
    m_normals = normals;
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

List3df Mesh::GetNormals()
{
    return m_normals;
}

GLuint Mesh::GetNumEdges()
{
    return 6*m_faces.rows();
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
        vertices[6*i+3] = m_normals(i,0);
        vertices[6*i+4] = m_normals(i,1);
        vertices[6*i+5] = m_normals(i,2);
    }

    // Transform F matrix into edge list
    GLuint n_F = m_faces.rows();
    GLuint indices[6*n_F];
    for(int i=0,j=0; i < n_F; i++,j+=6)
    {     
	indices[j]   = m_faces(i,0);
        indices[j+1] = m_faces(i,1);
		
	indices[j+4] = m_faces(i,1);
	indices[j+5] = m_faces(i,2);
        
	indices[j+2] = m_faces(i,2);
	indices[j+3] = m_faces(i,0);
    }

    //Eigen::Map<List3df>( vertices, m_vertices.rows(), m_vertices.cols() ) = m_vertices;

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
