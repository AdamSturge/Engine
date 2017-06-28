#include <time_integrator.h>

#ifndef VERLET_H
#define VERLET_H

class Verlet : public TimeIntegrator{

    public :
        /**
            Constructs an instance of Verlet with a default grid size
        **/
        Verlet();

        /**
            Constructs an instance of Verlet with the provided grid size
            @param dt difference between two points on the grid
        **/
        Verlet(GLfloat dt);

    private:

        /**
            Solves Newton's equations of motion.
            Updates entity_ptr buffers with next predicted position and velocity
            @param scene scene containing entities to be integrated forward
            @param entity_ptr pointer to entity to be integrated forward
        **/
       void Solve(
            const Scene& scene,
            const std::shared_ptr<PhysicsEntity> entity_ptr);
        
};
#endif
