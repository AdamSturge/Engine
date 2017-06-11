#include <mesh.h>
#include <Eigen/Core>
#include <vector3G.h>

#ifndef MODEL
#define MODEL
/**
    \brief Defines a model used for rendering

    Model is the base class for all entities that are rendered in a scene. It stores properites such as the mesh, material properties, textures, etc. It also holds the <b>model matrix</b> which handles transforming the mesh from local coordinates to world coordinates. See [Here](https://learnopengl.com/#!Getting-started/Coordinate-Systems) for more details.
**/
class Model {
   public:
        /**
            @return The model matrix
        **/
        Eigen::Matrix<GLfloat,4,4> GetModelMatrix();
       
        /**
            Sets the model matrix
            @param model Matrix to be set as the model matrix
        **/ 
        void SetModelMatrix(Eigen::Matrix<GLfloat,4,4> model);

        /**
            @return Copy of the mesh used by this model
        **/
        Mesh GetMesh();
        
     protected:
        /**
            The mesh for this model
        **/
        Mesh m_mesh; 
        /**
            The model matrix. This handles transforming from local model coordinates to world coordinates
        **/
    	Eigen::Matrix<GLfloat,4,4> m_model_matrix;  
        
        /**
            Builds a Model with an empty mesh and identity model matrix
        **/
        Model();
    
};
#endif
