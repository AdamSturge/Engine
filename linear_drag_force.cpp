#include "linear_drag_force.h"

LinearDragForceGenerator::LinearDragForceGenerator()
{
    m_beta = 1.0f;
}

LinearDragForceGenerator::LinearDragForceGenerator(GLfloat beta)
{
    m_beta = beta;
}

GLfloat LinearDragForceGenerator::GetDragCoeff()
{
    return m_beta;
}

void LinearDragForceGenerator::SetDragCoeff(GLfloat beta)
{
     m_beta = beta;
}

void LinearDragForceGenerator::AccumulateForce(std::shared_ptr<PhysicsEntity> entity, Vector3Gf &F) const
{
    GLfloat mass = entity->GetMass();
    Vector3Gf v = entity->GetVelocity();

    F += -m_beta*mass*v;
}

void LinearDragForceGenerator::AccumulatedFdv(const std::shared_ptr<PhysicsEntity> entity, Eigen::Matrix<GLfloat,3,3> &dF) const
{
    Eigen::Matrix<GLfloat,3,3> I = Eigen::Matrix<GLfloat,3,3>::Identity();

    dF += m_beta*I;
}

