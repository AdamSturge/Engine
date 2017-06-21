#include <time_integrator.h>
#include <assert.h>

void TimeIntegrator::StepForward(
            const Vector3Gf xi,
            const Vector3Gf vi,
            const GLfloat mass,
            const Vector3Gf F,
            Vector3Gf &xf,
            Vector3Gf &vf)

{
    assert(mass > 0.0f);

    Solve(xi,vi,mass,F,xf,vf);
}
