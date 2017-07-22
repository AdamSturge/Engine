#include <net_force_accumulator.h>

NetForceAccumulator::NetForceAccumulator()
{

}

void NetForceAccumulator::AddConstantForce(Vector3Gf a)
{
    m_constant_forces.push_back(ConstantForceGenerator(a));
}

void NetForceAccumulator::EnableGravity(bool enable)
{
    gravity_on = enable;
}

void NetForceAccumulator::ComputeNetForce(
    const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
    const std::shared_ptr<PhysicsEntity> entity_ptr,
    Vector3Gf &force) const
{
    for(ConstantForceGenerator constant_force : m_constant_forces)
    {
        constant_force.AccumulateForce(entity_ptr,force);
    }

    if(gravity_on)
    {
        for(std::shared_ptr<PhysicsEntity> other_entity_ptr : entity_ptrs)
        {
            if(other_entity_ptr != entity_ptr)
            {
                m_gravity_force.AccumulateForce(entity_ptr,other_entity_ptr,force);
            }
        }
    }
    
}

void NetForceAccumulator::ComputeNetForceJacobian(
            const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr,
            Eigen::Matrix<GLfloat,3,3> &dFdx, 
            Eigen::Matrix<GLfloat,3,3> &dFdv) const
{
    for(std::shared_ptr<PhysicsEntity> other_entity_ptr : entity_ptrs)
    {
        if(other_entity_ptr != entity_ptr)
        {
            m_gravity_force.AccumulatedFdx(entity_ptr,other_entity_ptr,dFdx);
        }
    }

}

