#include <mesh.h>
#include <iostream>

Mesh::Mesh(){};

Mesh::Mesh(List3df vertices, List3di faces)
{
    m_vertices = vertices;
    m_faces = faces;
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
List3df Mesh::GetVertices()
{
    return m_vertices;
}

List3di Mesh::GetFaces()
{
    return m_faces;
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

    GLfloat vertices[3*m_vertices.rows()];
    //std::copy(m_vertices.data()->begin(),m_vertices->end(),vertices);

	Eigen::Map<List3df>( vertices, m_vertices.rows(), m_vertices.cols() ) = m_vertices;
	//for(int i = 0; i < 3*m_vertices.rows(); i+=3)
	//{
	//	std::cout << vertices[i] << "," << vertices[i+1] << "," << vertices[i+2] << std::endl;
	//}

    glBindBuffer(GL_ARRAY_BUFFER,m_VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
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
