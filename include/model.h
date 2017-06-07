#include <mesh.h>
#include <Eigen/Core>
#include <vector3G.h>

#ifndef MODEL
#define MODEL
class Model {
   public:
        Eigen::Matrix<GLfloat,4,4> GetModelMatrix();
        
        void SetModelMatrix(Eigen::Matrix<GLfloat,4,4> model);

        Mesh GetMesh();
        
     protected:
        Mesh m_mesh; 
    	Eigen::Matrix<GLfloat,4,4> m_model_matrix;  
        
        Model();
    
};
#endif
