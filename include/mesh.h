#include <vector>
#include <GL/glew.h>
#include <Eigen/Core>
#ifndef MESH
#define MESH
/**
    \brief Defines a mesh
    
     A mesh is represented by a list of vertices and edges. A vertex is a set of 3 floats representing a (x,y,z) pair in R^3. 
     An Edge is represented by a pair of indices into the vertex list. Vertices in edges are listed in clockwise order as they appear on the mesh.
     Once a mesh is built it is loaded onto the GPU so it can be rendered
**/

typedef Eigen::Matrix<GLfloat, Eigen::Dynamic, 3, Eigen::RowMajor> List3df;
typedef Eigen::Matrix<GLint, Eigen::Dynamic, 3, Eigen::RowMajor> List3di;

class Mesh
{
    private:        
    	List3df m_vertices; // Matrix of vertices in mesh
    	List3di m_faces; // Matrix of indices into vertex list in counter-clockwise order.
        List3df m_face_normals; // Matrix of face normals
        List3df m_vertex_normals; // Matrix of vertex normals
    	GLuint m_VAO;
    	GLuint m_VBO;
    	GLuint m_EBO;

	void GenerateVAO();

        void ComputeNormals();

    public:
        /**
            Builds a mesh with no vertices or edges
        **/
        Mesh();

        /**
            Builds a mesh with the provided vertices and edges
            @param vertices nx3 matrix of vertices for the mesh. 
            @param faces mx3 matrix of face indices for the mesh. Listed in counter-clockwise order
        **/
        Mesh(List3df vertices, List3di faces);

        /**
            @return A copy of the vertices in the mesh
        **/
        List3df GetVertices();

        /**
            @return A copy of the faces in the mesh
        **/
        List3di GetFaces();

        /**
            @return A copy of the face normals in the mesh
        **/
        List3df GetFaceNormals();

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
