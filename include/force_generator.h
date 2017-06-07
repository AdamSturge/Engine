#include <Eigen/Core>
#include <GL/glew.h>
#include <physics_entity.h>
#include <memory>
#include <vector3G.h>

#ifndef FORCE_GENERATOR
#define FORCE_GENERATOR
class ForceGenerator 
{
    public:
        virtual ~ForceGenerator() {};

        virtual void AccumulateForce(std::shared_ptr<PhysicsEntity> entity, Vector3Gf &F) = 0;

};
#endif
