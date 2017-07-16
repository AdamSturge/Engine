#include "midpoint_method.h"

MidpointMethod::MidpointMethod()
{
    m_dt = 0.1;
    m_backward_euler = BackwardEuler(0.5f*m_dt);
}

MidpointMethod::MidpointMethod(GLfloat dt)
{
    m_dt = dt;
    m_backward_euler = BackwardEuler(0.5f*m_dt);
}

void MidpointMethod::Solve(const Scene& scene,const std::shared_ptr<PhysicsEntity> entity_ptr)
{
    Vector3Gf xi = entity_ptr->GetPosition();
    Vector3Gf vi = entity_ptr->GetVelocity();
    
    m_backward_euler.StepForward(scene,entity_ptr);
    
    Vector3Gf xhalf = entity_ptr->GetNextPosition();
    Vector3Gf vhalf = entity_ptr->GetNextVelocity();

    Vector3Gf xf = 2*xhalf - xi;
    Vector3Gf vf = 2*vhalf - vi;

    entity_ptr->SetNextPosition(xf);
    entity_ptr->SetNextVelocity(vf);
    
}
