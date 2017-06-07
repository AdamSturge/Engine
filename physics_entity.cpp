#include <physics_entity.h>

PhysicsEntity::PhysicsEntity()
{
	m_position.setZero();

    m_next_position_buffer = m_position;
    
    m_velocity.setZero();

    m_next_velocity_buffer = m_velocity;

    m_mass = 1.0f;
}

PhysicsEntity::ENTITY_TYPE PhysicsEntity::GetEntityType()
{
    return m_entity_type;
};

Vector3Gf PhysicsEntity::GetPosition()
{
    return m_position;
};

void PhysicsEntity::SetNextPosition(Vector3Gf x)
{
    m_next_position_buffer = x;
};

Vector3Gf PhysicsEntity::GetVelocity()
{
    return m_velocity;
};

void PhysicsEntity::SetNextVelocity(Vector3Gf v)
{
    m_next_velocity_buffer = v;
};

GLfloat PhysicsEntity::GetMass()
{
    return m_mass;
}

void PhysicsEntity::UpdateFromBuffers()
{
    m_position = m_next_position_buffer;
    m_velocity = m_next_velocity_buffer;
}
