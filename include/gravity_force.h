#include <physics_entity.h>
#include <memory>
#include <vector3G.h>

#ifndef GRAVITY_FORCE_H
#define GRAVITY_FORCE_H

class GravityForceGenerator
{
    private :
        const GLfloat m_G = 4.0f;

    public :
        GravityForceGenerator();

        void AccumulateForce(const std::shared_ptr<PhysicsEntity> e1, const std::shared_ptr<PhysicsEntity> e2, Vector3Gf &F);
};

#endif
