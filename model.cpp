#include <model.h>

Model::Model()
{
  m_normal_matrix.setIdentity();
}

Mesh Model::GetMesh()
{
    return m_mesh;
}

Material Model::GetMaterial()
{
    return m_material;
}

Eigen::Matrix<GLfloat,3,3> Model::GetNormalMatrix()
{
    return m_normal_matrix;
}

void Model::OnModelMatrixUpdate()
{
  m_normal_matrix = m_model_matrix.block(0,0,3,3).inverse().transpose();
}
