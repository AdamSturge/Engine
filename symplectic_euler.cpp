#include <symplectic_euler.h>
#include <assert.h>
#include <iostream>

SymplecticEuler::SymplecticEuler()
{
    m_dt = 0.001;
};

SymplecticEuler::SymplecticEuler(GLfloat dt)
{
    m_dt = dt;
};

void SymplecticEuler::Solve(
            const Vector3Gf xi,
            const Vector3Gf vi,
            const GLfloat mass,
            const Vector3Gf F,
            Vector3Gf &xf,
            Vector3Gf &vf)
{   
    vf = vi + m_dt*(1/mass)*F;
    xf = xi + m_dt*vf;
       
};

