#include <time_integrator.h>
#include <assert.h>

void TimeIntegrator::StepForward(
            const NetForceAccumulator& net_force_accumulator,
            const std::vector<std::shared_ptr<PhysicsEntity>> &entity_ptrs,
            const std::shared_ptr<PhysicsEntity> entity_ptr)

{
    assert(entity_ptr->GetMass() > 0.0f);

    Solve(net_force_accumulator,entity_ptrs,entity_ptr);
}

GLfloat TimeIntegrator::GetStepSize()
{
    return m_dt;
}
