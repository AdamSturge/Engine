#include <net_force_accumulator.h>
#include <iostream> 

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

void NetForceAccumulator::EnableDrag(bool enable)
{
    drag_on = enable;
}

void NetForceAccumulator::SetDragCoeff(GLfloat beta)
{
    m_drag_force.SetDragCoeff(beta);
}

void NetForceAccumulator::AddSpring(Spring spring)
{
    m_springs[spring.id] = spring;
    m_entity_spring_map[spring.entity1_ptr->GetId()].push_back(spring.id);
    m_entity_spring_map[spring.entity2_ptr->GetId()].push_back(spring.id);
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

    if(drag_on)
    {
        m_drag_force.AccumulateForce(entity_ptr,force);
    }

    GLint pid = entity_ptr->GetId();
    // Have to use find() instead of [] since we declared the method as const
    std::unordered_map<GLint,std::vector<GLint>>::const_iterator spring_itr = m_entity_spring_map.find(pid);
    if(spring_itr != m_entity_spring_map.end())
    {
        std::vector<GLint> spring_ids = spring_itr->second;
        for(GLint spring_id : spring_ids)
        {
            Spring spring = m_springs.find(spring_id)->second;
            if(spring.entity1_ptr == entity_ptr)
            {
                m_spring_force.AccumulateForce(spring.k,spring.l0,spring.entity1_ptr,spring.entity2_ptr,force); 
            }
            else if(spring.entity2_ptr == entity_ptr)
            {
                // swap the order of entity1_ptr and entity2_ptr to produce the negative of the force
                m_spring_force.AccumulateForce(spring.k,spring.l0,spring.entity2_ptr,spring.entity1_ptr,force); 
            }
            else
            {
                // We done goofed. 
                std::cout << "Computing a spring force on an entity not in this spring. PID : " << pid << " SpringID : " << spring_id << std::endl;
            }
        }
    }

    //std::cout << pid << ":" << force.transpose() << std::endl; 
}

void NetForceAccumulator::ComputeNetForceJacobian(
            const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr,
            Eigen::Matrix<GLfloat,3,3> &dFdx, 
            Eigen::Matrix<GLfloat,3,3> &dFdv) const
{
    if(gravity_on)
    {
        for(std::shared_ptr<PhysicsEntity> other_entity_ptr : entity_ptrs)
        {
            if(other_entity_ptr != entity_ptr)
            {
                m_gravity_force.AccumulatedFdx(entity_ptr,other_entity_ptr,dFdx);
            }
        }
    }

    if(drag_on)
    {
        m_drag_force.AccumulatedFdv(entity_ptr,dFdv);
    }

    GLint pid = entity_ptr->GetId();
    // Have to use find() instead of [] since we declared the method as const
    std::unordered_map<GLint,std::vector<GLint>>::const_iterator spring_itr = m_entity_spring_map.find(pid);
    if(spring_itr != m_entity_spring_map.end())
    {
        std::vector<GLint> spring_ids = spring_itr->second;
        for(GLint spring_id : spring_ids)
        {
            Spring spring = m_springs.find(spring_id)->second;
            m_spring_force.AccumulatedFdx(spring.k,spring.l0,spring.entity1_ptr,spring.entity2_ptr,dFdx);
        }
    } 
}

