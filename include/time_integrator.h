#ifndef TIME_INTEGRATOR_H
#define TIME_INTEGRATOR_H
#include <Eigen/Core>
#include <GL/glew.h>
#include <vector3G.h>
#include <scene.h>

class Scene; // Forward definition of Scene

/**
    \brief An abstact base class for all grid based numerical ODE solvers for Newton's laws
**/
class TimeIntegrator
{
    protected:
        GLfloat m_dt;

    public:
         virtual ~TimeIntegrator(){};
        
        /**
            Public interface for all solvers. 
            Computes position and velocity updates by solving Newton's equations of motion.
            Updates entity_ptr buffers with next predicted position and velocity
            @param scene scene containing entities to be integrated forward
            @param entity_ptr pointer to the entity being updated
         **/
         void StepForward(
            const Scene& scene,
            const std::shared_ptr<PhysicsEntity> entity_ptr);

    private:
        /**
            Private implementation details for solver.
            @param scene scene containing entities to be integrated forward
            @param entity_ptr pointer to the entity being updated
        **/
         virtual void Solve(
            const Scene& scene,
            const std::shared_ptr<PhysicsEntity> entity_ptr) = 0;
};
#endif
