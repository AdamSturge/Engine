#include <model.h>

Model::Model()
{
	m_model_matrix.setIdentity();
}

Eigen::Matrix<GLfloat, 4, 4> Model::GetModelMatrix()
{
    return m_model_matrix;
};

void Model::SetModelMatrix(Eigen::Matrix<GLfloat,4,4> m)
{
    m_model_matrix = m;
};

Mesh Model::GetMesh()
{
    return m_mesh;
}
