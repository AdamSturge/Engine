#include <physics_entity.h>

std::atomic<GLint> PhysicsEntity::next_id(0);

PhysicsEntity::PhysicsEntity()
{
    m_id = PhysicsEntity::next_id++; // store current value of next_id and increment for next entity

    m_position.setZero();

    m_next_position = m_position;
    
    m_velocity.setZero();

    m_next_velocity = m_velocity;

    m_mass = 1.0f;

    m_inverse_inertia_tensor_local.setIdentity();
    
    m_inverse_inertia_tensor_world.setIdentity();

    m_orientation = Quaternion(0.0f,Vector3Gf(1.0f,0.0f,0.0f));

    m_next_orientation = m_orientation;

    m_angular_velocity.setZero();

    m_next_angular_velocity = m_angular_velocity;
}

PhysicsEntity::PhysicsEntity(Vector3Gf position, Vector3Gf velocity, GLfloat mass, Quaternion orientation, Vector3Gf angular_velocity)
{
    m_id = PhysicsEntity::next_id++; // store current value of next_id and increment for next entity

    m_position = position;

    m_next_position = m_position;

    m_velocity = velocity;

    m_next_velocity = m_velocity;

    m_mass = mass;

    m_inverse_inertia_tensor_local.setIdentity();
    
    m_inverse_inertia_tensor_world.setIdentity();

    m_orientation = orientation / orientation.norm();

    m_next_orientation = m_orientation;

    m_angular_velocity = angular_velocity;

    m_next_angular_velocity = angular_velocity;
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
    m_next_position = x;
};

Vector3Gf PhysicsEntity::GetNextPosition()
{
    return m_next_position;
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
    m_next_velocity = v;
};

Vector3Gf PhysicsEntity::GetNextVelocity()
{
    return m_next_velocity;
};

GLfloat PhysicsEntity::GetMass()
{
    return m_mass;
}

Quaternion PhysicsEntity::GetOrientation()
{
    return m_orientation;
}

void PhysicsEntity::SetOrientation(Quaternion q)
{
    m_orientation = q;
}

Quaternion PhysicsEntity::GetNextOrientation()
{
    return m_next_orientation;
}

void PhysicsEntity::SetNextOrientation(Quaternion q)
{
    m_next_orientation = q;
}

Vector3Gf PhysicsEntity::GetAngularVelocity()
{
    return m_angular_velocity;
}

void PhysicsEntity::SetAngularVelocity(Vector3Gf w)
{
    m_angular_velocity = w;
}

Vector3Gf PhysicsEntity::GetNextAngularVelocity()
{
    return m_next_angular_velocity;
}

void PhysicsEntity::SetNextAngularVelocity(Vector3Gf w)
{
    m_next_angular_velocity = w;
}

void PhysicsEntity::SetLocalInertiaTensor(Eigen::Matrix<GLfloat,3,3> I)
{
  m_inverse_inertia_tensor_local = I.inverse();
}

void PhysicsEntity::OnModelMatrixUpdate()
{
  m_inverse_inertia_tensor_world = m_model_matrix.block(0,0,3,3)*m_inverse_inertia_tensor_local;
}

void PhysicsEntity::UpdateFromBuffers()
{
    m_position = m_next_position;
    m_velocity = m_next_velocity;
    m_orientation = m_next_orientation;
    m_angular_velocity = m_next_angular_velocity;
    OnUpdateFromBuffers();
}
