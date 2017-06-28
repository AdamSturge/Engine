#include <time_integrator.h>
#include <assert.h>

void TimeIntegrator::StepForward(
            const Scene& scene,
            const std::shared_ptr<PhysicsEntity> entity_ptr)

{
    assert(entity_ptr->GetMass() > 0.0f);

    Solve(scene,entity_ptr);
}
