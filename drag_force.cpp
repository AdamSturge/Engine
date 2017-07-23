#include "drag_force.h"

DragForceGenerator::DragForceGenerator()
{
    m_beta = 1.0f;
}

DragForceGenerator::DragForceGenerator(GLfloat beta)
{
    m_beta = beta;
}

GLfloat DragForceGenerator::GetDragCoeff()
{
    return m_beta;
}

void DragForceGenerator::SetDragCoeff(GLfloat beta)
{
     m_beta = beta;
}

void DragForceGenerator::AccumulateForce(std::shared_ptr<PhysicsEntity> entity, Vector3Gf &F) const
{
    GLfloat mass = entity->GetMass();
    Vector3Gf v = entity->GetVelocity();

    F += -m_beta*mass*v;
}

void DragForceGenerator::AccumulatedFdv(const std::shared_ptr<PhysicsEntity> entity, Eigen::Matrix<GLfloat,3,3> &dF) const
{
    Eigen::Matrix<GLfloat,3,3> I = Eigen::Matrix<GLfloat,3,3>::Identity();

    dF += m_beta*I;
}

