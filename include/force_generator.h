#include <Eigen/Core>
#include <GL/glew.h>
#include <physics_entity.h>
#include <memory>
#include <vector3G.h>


#ifndef FORCE_GENERATOR
#define FORCE_GENERATOR
/**
    \brief NO LONGER USED. REMOVE LATER.  Abstract base class for all force generators

    A force generator is an abstraction of a particular kind of force acting on a PhysicsEntity. The exact nature of the force depends on the implementaiton of the AccumulateForce method
**/
class ForceGenerator 
{
    public:
        virtual ~ForceGenerator() {};

        /**
            Computes a force through accumulation. Meaning the result is added to the value stored in F
            @param entity PhysicsEntity the force is acting on
            @param F Force vector which will be modified to add in the force represented by this generator
        **/
        virtual void AccumulateForce(std::shared_ptr<PhysicsEntity> entity, Vector3Gf &F) = 0;

};
#endif
