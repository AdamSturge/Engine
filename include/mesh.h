#include <vector>
#include <GL/glew.h>
#ifndef MESH
#define MESH
/**
    \brief Defines a mesh
    
     A mesh is represented by a list of vertices and edges. A vertex is a set of 3 floats representing a (x,y,z) pair in R^3. 
     An Edge is represented by a pair of indices into the vertex list. Vertices in edges are listed in clockwise order as they appear on the mesh.
     Once a mesh is built it is loaded onto the GPU so it can be rendered
**/
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
        /**
            Builds a mesh with no vertices or edges
        **/
        Mesh();

        /**
            Builds a mesh with the provided vertices and edges
            @param vertices List of vertices for the mesh. It's length should be a multiple of 3
            @param edges List of edges for the mesh. Listed in clockwise order
        **/
        Mesh(std::vector<GLfloat> vertices, std::vector<std::pair<GLuint,GLuint>> edges);
/*
        ~Mesh();

        Mesh(const Mesh& other);

        Mesh(Mesh&& other);

        Mesh& operator=(const Mesh& other);

        Mesh& operator=(Mesh&& other);
*/

        /**
            @return A copy of the vertices in the mesh
        **/
        std::vector<GLfloat> GetVertices();

        /**
            @return A copy of the edges in the mesh
        **/
        std::vector<std::pair<GLuint,GLuint>> GetEdges();

        /**
            @return The number of edges in the mesh
        **/
        GLuint GetNumEdges();

	/**
            @return The vertex array buffer index for this mesh
        **/
        GLuint GetVAO();

        /**
            Removes the mesh from the GPU
        **/
        void CleanUp();
    
};
#endif
