#include "local_coordinate_entity.h"

LocalCoordinateEntity::LocalCoordinateEntity()
{
  m_model_matrix.setIdentity();
}

LocalCoordinateEntity::~LocalCoordinateEntity()
{

}

Eigen::Matrix<GLfloat, 4, 4> LocalCoordinateEntity::GetModelMatrix()
{
    return m_model_matrix;
};

void LocalCoordinateEntity::SetModelMatrix(Eigen::Matrix<GLfloat,4,4> m)
{
    m_model_matrix = m;
    OnModelMatrixUpdate();
};


