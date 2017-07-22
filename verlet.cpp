#include <verlet.h>

Verlet::Verlet()
{
    m_dt = 0.001;
};

Verlet::Verlet(GLfloat dt)
{
    m_dt = dt;
};

void Verlet::Solve(
            const NetForceAccumulator& net_force_accumulator,
			const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr)
{
    const Vector3Gf xi = entity_ptr->GetPosition();
    const Vector3Gf vi = entity_ptr->GetVelocity();
    const GLfloat mass = entity_ptr->GetMass();

    Vector3Gf Fi,Ff,ai,xf,af,vf;
    
    Fi.setZero();
    net_force_accumulator.ComputeNetForce(entity_ptrs,entity_ptr,Fi);

    ai = (1/mass)*Fi;
    xf = xi + m_dt*vi + 0.5f*m_dt*m_dt*ai;
    
    entity_ptr->SetNextPosition(xf);
    entity_ptr->UpdateFromBuffers(); // Load xf into position slot for computing F(x(t+h))

    Ff.setZero();
    net_force_accumulator.ComputeNetForce(entity_ptrs,entity_ptr,Ff); // Compute F(x(t+h))

    entity_ptr->SetNextPosition(xi); // Load xi back into position slot as to not affect force calulations for other entities
    entity_ptr->UpdateFromBuffers();

    af = (1/mass)*Ff;
    vf = vi + 0.5f*m_dt*(ai + af);

    entity_ptr->SetNextPosition(xf);
    entity_ptr->SetNextVelocity(vf);
};

