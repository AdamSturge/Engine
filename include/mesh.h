#include <vector>
#include <GL/glew.h>
#ifndef MESH
#define MESH
class Mesh
{
    private:        
    	std::vector<GLfloat> m_vertices; // list of vertices in mesh
    	std::vector<std::pair<GLuint,GLuint>> m_edges; // list of pairs of indices into vertex list in clockwise order.
    	GLuint m_VAO;
    	GLuint m_VBO;
    	GLuint m_EBO;

	void GenerateVAO();

    public:
        Mesh();

        Mesh(std::vector<GLfloat> vertices, std::vector<std::pair<GLuint,GLuint>> edges);
/*
        ~Mesh();

        Mesh(const Mesh& other);

        Mesh(Mesh&& other);

        Mesh& operator=(const Mesh& other);

        Mesh& operator=(Mesh&& other);
*/
        std::vector<GLfloat> GetVertices();

        std::vector<std::pair<GLuint,GLuint>> GetEdges();

        GLuint GetNumEdges();

	GLuint GetVAO();

        void CleanUp();
    
};
#endif
