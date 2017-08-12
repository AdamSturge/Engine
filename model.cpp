#include <model.h>

Model::Model()
{
	m_model_matrix.setIdentity();
        m_normal_matrix.setIdentity();
}

Eigen::Matrix<GLfloat, 4, 4> Model::GetModelMatrix()
{
    return m_model_matrix;
};

void Model::SetModelMatrix(Eigen::Matrix<GLfloat,4,4> m)
{
    m_model_matrix = m;
    m_normal_matrix = m.block(0,0,3,3).inverse().transpose();
};

Mesh Model::GetMesh()
{
    return m_mesh;
}

Eigen::Matrix<GLfloat,3,3> Model::GetNormalMatrix()
{
    return m_normal_matrix;
}
