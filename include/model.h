#ifndef MODEL
#define MODEL
#include <mesh.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector3G.h>
#include <material.h>
#include "local_coordinate_entity.h"
/**
    \brief Defines a model used for rendering

    Model is the base class for all entities that are rendered in a scene. It stores properites such as the mesh, material properties, textures, etc. It also holds the <b>model matrix</b> which handles transforming the mesh from local coordinates to world coordinates. See [Here](https://learnopengl.com/#!Getting-started/Coordinate-Systems) for more details.
**/
class Model : virtual public LocalCoordinateEntity {
   public:
        /**
            @return Copy of the mesh used by this model
        **/
        Mesh GetMesh();

        /**
            #return material for this mesh
        **/
        Material GetMaterial();

        /**
            @return The normal matrix
        **/
        Eigen::Matrix<GLfloat,3,3> GetNormalMatrix();
        
     protected:
        /**
            The mesh for this model
        **/
        Mesh m_mesh; 

        /**
            Material properties for this model
        **/
        Material m_material;
        
        /**
            The normal matrix. Used in rendering light interaction with surface
        **/
        Eigen::Matrix<GLfloat,3,3> m_normal_matrix;
        
        /**
            Builds a Model with an empty mesh and identity model matrix
        **/
        Model();

	void OnModelMatrixUpdate();
    
};
#endif
