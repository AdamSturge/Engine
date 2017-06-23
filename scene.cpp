#include <scene.h>
#include <memory>
#include <explicit_euler.h>
#include <iostream>
#include <sphere.h>

Scene::Scene()
{ 
    m_time_integrator = std::shared_ptr<TimeIntegrator>(new ExplicitEuler(0.01f));
    m_constant_force_generator = ConstantForceGenerator(Vector3Gf(0.0f,0.0f,0.0f));
};

Scene::Scene(std::shared_ptr<TimeIntegrator> integrator, ConstantForceGenerator cfg)
{
    m_time_integrator = integrator;
    m_constant_force_generator = cfg;
}

void Scene::AddPhysicsEntity(std::shared_ptr<PhysicsEntity> entity_ptr)
{
    m_physics_entity_ptrs.push_back(entity_ptr);
};

void Scene::GetPhysicsEntity(const GLuint index, std::shared_ptr<PhysicsEntity> &entity_ptr)
{
    entity_ptr = m_physics_entity_ptrs[index];
};

void Scene::AddModel(std::shared_ptr<Model> model_ptr)
{
    m_model_ptrs.push_back(model_ptr);
};

void Scene::GetModel(const GLuint index, std::shared_ptr<Model> &model_ptr, GLuint &VAO)
{
    model_ptr = m_model_ptrs[index];
    VAO = model_ptr->GetMesh().GetVAO();
};

GLuint Scene::GetPhysicsEntityCount()
{
    return m_physics_entity_ptrs.size();
}

GLuint Scene::GetModelCount()
{
    return m_model_ptrs.size();
}

void Scene::StepPhysics()
{
    for(std::shared_ptr<PhysicsEntity> entity_ptr : m_physics_entity_ptrs)
    {
        PhysicsEntity::ENTITY_TYPE entity_type = entity_ptr->GetEntityType();
        switch(entity_type)
        {
            case PhysicsEntity::ENTITY_TYPE::SPHERE_ENTITY :
            {    
                //std::shared_ptr<Sphere> derived_entity_ptr = std::static_pointer_cast<Sphere>(entity_ptr);
                //StepPhysicsWithType<Sphere>(derived_entity_ptr);
                break;
            }
        }
    }

    for(std::shared_ptr<PhysicsEntity> entity_ptr : m_physics_entity_ptrs)
    {
        PhysicsEntity::ENTITY_TYPE entity_type = entity_ptr->GetEntityType();
        switch(entity_type)
        {
            case PhysicsEntity::ENTITY_TYPE::SPHERE_ENTITY :
            {    
                //std::shared_ptr<Sphere> derived_entity_ptr = std::static_pointer_cast<Sphere>(entity_ptr);
                //derived_entity_ptr->UpdateFromBuffers();
                break;
            }
        }
    }

};
template <class T>
void Scene::StepPhysicsWithType(std::shared_ptr<T> entity_ptr)
{
        Vector3Gf xi = entity_ptr->GetPosition();
        Vector3Gf vi = entity_ptr->GetVelocity();
        GLfloat mass = entity_ptr->GetMass();

        Vector3Gf force;
        force.setZero();

        ComputeNetForce(entity_ptr,force);

        //std::cout << force << std::endl << std::endl;

        Vector3Gf xf;
        Vector3Gf vf;

        m_time_integrator->StepForward(xi,vi,mass,force,xf,vf);

        entity_ptr->SetNextPosition(xf);
        entity_ptr->SetNextVelocity(vf);
 
};

void Scene::ComputeNetForce(const std::shared_ptr<PhysicsEntity> entity_ptr, Vector3Gf &force)
{
    m_constant_force_generator.AccumulateForce(entity_ptr,force);
};

void Scene::Render(Shader shader)
{
    GLint modelLoc = glGetUniformLocation(shader.Program, "model");

    const GLuint model_count = GetModelCount();
    std::shared_ptr<Model> model_ptr;
    for(int i = 0; i < model_count; ++i)
    {
        GLuint VAO;
 
        GetModel(i,model_ptr,VAO); 
       
        Eigen::Matrix<float,4,4> model_matrix = model_ptr->GetModelMatrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model_matrix.data());  
        
        glBindVertexArray(VAO);
        
        glDrawElements(GL_TRIANGLES, model_ptr->GetMesh().GetNumEdges(), GL_UNSIGNED_INT,0);

        glBindVertexArray(0);   

    }
}

void Scene::CleanUp()
{
    const GLuint model_count = GetModelCount();
    std::shared_ptr<Model> model_ptr;
    for(int i = 0; i < model_count; ++i)
    {
        GLuint VAO; 
        GetModel(i,model_ptr,VAO); 
        model_ptr->GetMesh().CleanUp();   
    }
}


