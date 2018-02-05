#ifndef LOCAL_COORDIANTE_ENTITY_H
#define LOCAL_COORDIANTE_ENTITY_H

#include <Eigen/Dense>
#include "vector3G.h"
/*
 * \brief Defines an entity that tracks how to transform from it's own local coordiante sytem to world coordinates
 */
class LocalCoordinateEntity{

  public:

        LocalCoordinateEntity();

	~LocalCoordinateEntity();

	/**
            @return The model matrix
        **/
        Eigen::Matrix<GLfloat,4,4> GetModelMatrix();
       
        /**
            Sets the model matrix
            @param model Matrix to be set as the model matrix
        **/ 
        void SetModelMatrix(Eigen::Matrix<GLfloat,4,4> model);


  protected:
	/**
            The model matrix. This handles transforming from local model coordinates to world coordinates
        **/
    	Eigen::Matrix<GLfloat,4,4> m_model_matrix; 

        virtual void OnModelMatrixUpdate() = 0;	


};
#endif
