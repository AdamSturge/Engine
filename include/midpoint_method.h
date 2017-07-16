#ifndef MIDPOINT_METHOD_H
#define MIDPOINT_METHOD_H
#include "time_integrator.h"
#include "backward_euler.h"
#include "explicit_euler.h"
/**
    \brief Implementation of Midpoint method for solving Newton's Laws
**/
class MidpointMethod : public TimeIntegrator
{
    public:
        MidpointMethod();

        MidpointMethod(GLfloat dt);

    private:
        BackwardEuler m_backward_euler;

        /**
            Private implementation details for solver.
            @param scene scene containing entities to be integrated forward
            @param entity_ptr pointer to the entity being updated
        **/
        void Solve(const Scene& scene,const std::shared_ptr<PhysicsEntity> entity_ptr);
       
};
#endif
