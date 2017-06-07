#include <game_entity.h>
#include <iostream>

GameEntity::GameEntity()
{   
    m_position.setZero();

    m_next_position_buffer = m_position;
    
    m_velocity.setZero();

    m_next_velocity_buffer = m_velocity;

    m_mass = 1.0f;

    m_model_matrix.setIdentity();
}

GameEntity::ENTITY_TYPE GameEntity::GetEntityType()
{
    return m_entity_type;
};

Eigen::Matrix<GLfloat, 4, 4> GameEntity::GetModelMatrix()
{
    return m_model_matrix;
};

void GameEntity::SetModelMatrix(Eigen::Matrix<GLfloat,4,4> m)
{
    m_model_matrix = m;
};

Mesh GameEntity::GetMesh()
{
    return m_mesh;
}

Vector3Gf GameEntity::GetPosition()
{
    return m_position;
};

void GameEntity::SetNextPosition(Vector3Gf x)
{
    m_next_position_buffer = x;
};

Vector3Gf GameEntity::GetVelocity()
{
    return m_velocity;
};

void GameEntity::SetNextVelocity(Vector3Gf v)
{
    m_next_velocity_buffer = v;
};

GLfloat GameEntity::GetMass()
{
    return m_mass;
}

void GameEntity::UpdateFromBuffers()
{
    m_position = m_next_position_buffer;
    m_velocity = m_next_velocity_buffer;
}


