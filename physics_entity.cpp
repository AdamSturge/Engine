#include <physics_entity.h>

std::atomic<GLint> PhysicsEntity::next_id(0);

PhysicsEntity::PhysicsEntity()
{
    m_id = PhysicsEntity::next_id++; // store current value of next_id and increment for next entity

    m_position.setZero();

    m_next_position_buffer = m_position;
    
    m_velocity.setZero();

    m_next_velocity_buffer = m_velocity;

    m_mass = 1.0f;
    
    m_orientation = Quaternion(0.0f,Vector3Gf(1.0f,0.0f,0.0f));
}

PhysicsEntity::PhysicsEntity(Vector3Gf position, Vector3Gf velocity, GLfloat mass, Quaternion orientation)
{
    m_id = PhysicsEntity::next_id++; // store current value of next_id and increment for next entity

    m_position = position;

    m_next_position_buffer = m_position;

    m_velocity = velocity;

    m_next_velocity_buffer = m_velocity;

    m_mass = mass;

    m_orientation = orientation;
}

GLint PhysicsEntity::GetId() const
{
    return m_id;
}

Vector3Gf PhysicsEntity::GetPosition()
{
    return m_position;
};

void PhysicsEntity::SetPosition(Vector3Gf x)
{
    m_position = x;
}

void PhysicsEntity::SetNextPosition(Vector3Gf x)
{
    m_next_position_buffer = x;
};

Vector3Gf PhysicsEntity::GetNextPosition()
{
    return m_next_position_buffer;
};

Vector3Gf PhysicsEntity::GetVelocity()
{
    return m_velocity;
};

void PhysicsEntity::SetVelocity(Vector3Gf v)
{
    m_velocity = v;
}

void PhysicsEntity::SetNextVelocity(Vector3Gf v)
{
    m_next_velocity_buffer = v;
};

Vector3Gf PhysicsEntity::GetNextVelocity()
{
    return m_next_velocity_buffer;
};

GLfloat PhysicsEntity::GetMass()
{
    return m_mass;
}

void PhysicsEntity::UpdateFromBuffers()
{
    m_position = m_next_position_buffer;
    m_velocity = m_next_velocity_buffer;
    OnUpdateFromBuffers();
}
