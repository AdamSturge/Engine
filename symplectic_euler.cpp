#include <symplectic_euler.h>
#include <assert.h>
#include <iostream>

SymplecticEuler::SymplecticEuler()
{
    m_dt = 0.001;
};

SymplecticEuler::SymplecticEuler(GLfloat dt)
{
    m_dt = dt;
};

void SymplecticEuler::Solve(
            const NetForceAccumulator& net_force_accumulator,
	    const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr)
{   
    Vector3Gf xi = entity_ptr->GetPosition();
    Vector3Gf vi = entity_ptr->GetVelocity();
    GLfloat mass = entity_ptr->GetMass();

    Vector3Gf F;
    F.setZero();
    net_force_accumulator.ComputeNetForce(entity_ptrs,entity_ptr,F);

    Vector3Gf vf = vi + m_dt*(1/mass)*F; 
    Vector3Gf xf = xi + m_dt*vf;
    
    entity_ptr->SetNextPosition(xf);
    entity_ptr->SetNextVelocity(vf);
};

