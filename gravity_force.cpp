#include <gravity_force.h>

GravityForceGenerator::GravityForceGenerator(){};

void GravityForceGenerator::AccumulateForce(const std::shared_ptr<PhysicsEntity> e1, const std::shared_ptr<PhysicsEntity> e2, Vector3Gf &F) const
{
    GLfloat m1 = e1->GetMass();
    GLfloat m2 = e2->GetMass();

    Vector3Gf x1 = e1->GetPosition();
    Vector3Gf x2 = e2->GetPosition();

    Vector3Gf n = x2 - x1;
    GLfloat r = n.norm();
    n = n/r;
     
    if(r >= 1.0f)
    {
        F += (m_G*m1*m2/(r*r))*n;
    }

};
