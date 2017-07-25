#include <scene.h>
#include <memory>
#include <explicit_euler.h>
#include <iostream>
#include <sphere.h>

Scene::Scene()
{ 
    m_time_integrator = std::shared_ptr<TimeIntegrator>(new ExplicitEuler(0.01f));
};

Scene::Scene(std::shared_ptr<TimeIntegrator> integrator, NetForceAccumulator net_force_accumulator)
{
    m_time_integrator = integrator;
    m_net_force_accumulator = net_force_accumulator;
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

void Scene::AddSpring(Spring spring)
{
    m_net_force_accumulator.AddSpring(spring);
}

void Scene::StepPhysics()
{
    for(std::shared_ptr<PhysicsEntity> entity_ptr : m_physics_entity_ptrs)
    {
        m_time_integrator->StepForward(m_net_force_accumulator,m_physics_entity_ptrs,entity_ptr);
    }

    for(std::shared_ptr<PhysicsEntity> entity_ptr : m_physics_entity_ptrs)
    {
        entity_ptr->UpdateFromBuffers();
    }

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


