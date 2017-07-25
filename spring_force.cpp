#include <spring_force.h>

SpringForceGenerator::SpringForceGenerator(){};

void SpringForceGenerator::AccumulateForce(
    const GLfloat k, 
    const GLfloat l0, 
    const std::shared_ptr<PhysicsEntity> entity1_ptr, 
    const std::shared_ptr<PhysicsEntity> entity2_ptr, 
    Vector3Gf &F) const
{
    Vector3Gf x1 = entity1_ptr->GetPosition();
    Vector3Gf x2 = entity2_ptr->GetPosition();

    Vector3Gf n = x2 - x1;
    GLfloat l = n.norm();
    n = n/l;

    F += k*(l - l0)*n;
}

void SpringForceGenerator::AccumulatedFdx(const Spring spring, Eigen::Matrix<GLfloat,3,3> &dF) const
{

}

