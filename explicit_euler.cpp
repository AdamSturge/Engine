#include <explicit_euler.h>
#include <assert.h>
#include <iostream>

ExplicitEuler::ExplicitEuler()
{
    m_dt = 0.001;
};

ExplicitEuler::ExplicitEuler(GLfloat dt)
{
    m_dt = dt;
};

void ExplicitEuler::Solve(
            const NetForceAccumulator& net_force_accumulator,
	    const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr)
{   
    const Vector3Gf xi = entity_ptr->GetPosition();
    const Vector3Gf vi = entity_ptr->GetVelocity();
    const GLfloat mass = entity_ptr->GetMass();
    const Quaternion oi = entity_ptr->GetOrientation();
    const Vector3Gf  wi = entity_ptr->GetAngularVelocity();
   
    Vector3Gf F;
    F.setZero();
    net_force_accumulator.ComputeNetForce(entity_ptrs,entity_ptr,F);

    Vector3Gf xf = xi + m_dt*vi;
    Vector3Gf vf = vi + m_dt*(1/mass)*F; 

    entity_ptr->SetNextPosition(xf);
    entity_ptr->SetNextVelocity(vf);  

    Quaternion of = oi + 0.5*m_dt*Quaternion(wi)*oi;

    entity_ptr->SetNextOrientation(of);

};

