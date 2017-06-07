#include <constant_force.h>

ConstantForceGenerator::ConstantForceGenerator()
{
    m_accel = Vector3Gf(0.0f,0.0f,0.0f);
};


ConstantForceGenerator::ConstantForceGenerator(Vector3Gf accel)
{
    m_accel = accel;
};

ConstantForceGenerator::~ConstantForceGenerator(){};

void ConstantForceGenerator::AccumulateForce(std::shared_ptr<PhysicsEntity> entity, Vector3Gf &F)
{
    GLfloat mass = entity->GetMass();
    
    F = mass*m_accel.transpose(); // TO DO: Store transpose instead of computing each time
    
};
