#include <backward_euler.h>
#include <Eigen/Dense>
#include <iostream>

BackwardEuler::BackwardEuler()
{
    m_dt = 0.01;
}

BackwardEuler::BackwardEuler(GLfloat dt)
{
    m_dt = dt;
}

void BackwardEuler::Solve(const Scene& scene,const std::shared_ptr<PhysicsEntity> entity_ptr)
{
    Vector3Gf xi = entity_ptr->GetPosition();
    Vector3Gf vi = entity_ptr->GetVelocity();
    GLfloat mass = entity_ptr->GetMass();

    // Set initial guess z_0 by using Symplectic Euler
    Vector3Gf F;
    F.setZero();
    scene.ComputeNetForce(entity_ptr,F);
    Vector3Gf vf = vi + m_dt*F/mass;
    Vector3Gf xf = xi + m_dt*vf;

    entity_ptr->SetPosition(xf);
    entity_ptr->SetVelocity(vf);

    GLfloat diff = 100.0f;
    Eigen::Matrix<GLfloat,6,6> J;
    Eigen::Matrix<GLfloat,3,3> dFdx,dFdv;
    Eigen::Matrix<GLfloat,6,1> G;    
    Eigen::Matrix<GLfloat,6,1> delta;
    for(int i = 0; i < 3 && diff > 1e-9; ++i)
    {
        // Compute Jacobian at current guess
        J.setZero();
        dFdx.setZero();
        dFdv.setZero();
        scene.ComputeForceJacobian(entity_ptr,dFdx,dFdv);
        ComputeJacobian(mass,dFdx,dFdv,J);
        
        // Compute force at current guess
        F.setZero();
        scene.ComputeNetForce(entity_ptr,F);

        // Compute G for current guess
        G.topRows(3) = xf - xi - m_dt*vf;
        G.bottomRows(3) = vf - vi - m_dt*F/mass;

        // Solve for delta
        delta = J.ldlt().solve(-G);

        // Update guess
        xf = xf + delta.topRows(3);
        vf = vf + delta.bottomRows(3);

        // Load guess into entity for Jacobian and force computations
        entity_ptr->SetPosition(xf);
        entity_ptr->SetVelocity(vf);

        diff = delta.squaredNorm();
     }

    entity_ptr->SetNextPosition(xf);
    entity_ptr->SetNextVelocity(vf);

}


void BackwardEuler::ComputeJacobian(
                                    const GLfloat mass, 
                                    const Eigen::Matrix<GLfloat,3,3> dFdx, 
                                    const Eigen::Matrix<GLfloat,3,3> dFdv, 
                                    Eigen::Matrix<GLfloat,6,6> &J) const
{
    Eigen::Matrix<GLfloat,3,3> I = Eigen::Matrix<GLfloat,3,3>::Identity();
    J.block(0,0,3,3) = I;

    J.block(0,3,3,3) = m_dt*I;

    J.block(3,0,3,3) = -(m_dt/mass)*dFdx;

    J.block(3,3,3,3) = I - (m_dt/mass)*dFdv;
};

