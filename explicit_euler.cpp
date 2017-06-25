#include <explicit_euler.h>
#include <assert.h>
#include <iostream>

ExplicitEuler::ExplicitEuler()
{
    m_dt = 0.001;
};

ExplicitEuler::ExplicitEuler(GLfloat dt)
{
    m_dt = dt;
};

void ExplicitEuler::Solve(
            const Vector3Gf xi,
            const Vector3Gf vi,
            const GLfloat mass,
            const Vector3Gf F,
            Vector3Gf &xf,
            Vector3Gf &vf)
{   
    xf = xi + m_dt*vi;
    vf = vi + m_dt*(1/mass)*F;   
};

