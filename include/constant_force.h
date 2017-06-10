#include <force_generator.h>
#include <vector3G.h>

#ifndef CONSTANT_FORCE_GENERATOR
#define CONSTANT_FORCE_GENERATOR
/**
    \brief A constant force throughout all space 
**/
class ConstantForceGenerator : public ForceGenerator
{
    private:
        /** Spacially and temporarly uniform acceleration vector represeting constant force **/
        Vector3Gf m_accel;
    public:
        /**
            Builds a ConstantForceGenerator with a zero acceleration at all points in space.
        **/
        ConstantForceGenerator();
    
        /**
            Builds a ConstantForceGenerator with a given acceleration at all points in space
            @param accel acceleration vector for the force
        **/
        ConstantForceGenerator(Vector3Gf accel);

        /**
            Deconstructs a ConstantForceGenerator
        **/
        ~ConstantForceGenerator();
        
        /**
            Adds a constant force determined by the mass of the provided entity and the stored acceleration vector
            @param entity Entity whom the force will be applied against
            @param F Force vector that will accumulate the constant force represented by this instance
        **/
        void AccumulateForce(std::shared_ptr<PhysicsEntity> entity, Vector3Gf &F);

};
#endif
