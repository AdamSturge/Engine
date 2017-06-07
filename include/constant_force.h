#include <force_generator.h>
#include <vector3G.h>

#ifndef CONSTANT_FORCE_GENERATOR
#define CONSTANT_FORCE_GENERATOR
class ConstantForceGenerator : public ForceGenerator
{
    private:
        Vector3Gf m_accel;
    
    public:
        ConstantForceGenerator();
    
        ConstantForceGenerator(Vector3Gf accel);

        ~ConstantForceGenerator();
        
        void AccumulateForce(std::shared_ptr<PhysicsEntity> entity, Vector3Gf &F);

};
#endif
