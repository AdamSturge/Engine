#include <physics_entity.h>
#include <model.h>
#include <memory>
#include <vector3G.h>
#include <time_integrator.h>
#include <constant_force.h>
#include <shader.h>
#include <camera.h>
#include <GLFW/glfw3.h>

#ifndef SCENE
#define SCENE
class Scene
{
    private:    
	std::vector<std::shared_ptr<PhysicsEntity>> m_physics_entity_ptrs;
	std::vector<std::shared_ptr<Model>> m_model_ptrs;
        std::shared_ptr<TimeIntegrator> m_time_integrator;
        ConstantForceGenerator m_constant_force_generator;
            
        template <class T>
        void StepPhysicsWithType(std::shared_ptr<T> entity_ptr);

	void static MouseCallback(GLFWwindow*,double xpos, double ypos);

	void staticScrollCallback(GLFWwindow*, double xoffset, double yoffset);

	void BindCameraEventListeners();
	

    public :
        Scene();

        Scene(std::shared_ptr<TimeIntegrator> integrator, ConstantForceGenerator cfg);

        void AddPhysicsEntity(std::shared_ptr<PhysicsEntity> entity_ptr);

        void GetPhysicsEntity(const GLuint index, std::shared_ptr<PhysicsEntity> &entity_ptr);

	void AddModel(std::shared_ptr<Model> model_ptr);

        void GetModel(const GLuint index, std::shared_ptr<Model> &model_ptr, GLuint &VAO);

        GLuint GetPhysicsEntityCount();

	GLuint GetModelCount();

        void StepPhysics();

        void ComputeNetForce(const std::shared_ptr<PhysicsEntity> entity_ptr, Vector3Gf &force);

        void Render(Shader shader);

	void CleanUp();

	void DoMovement(GLfloat deltaTime, bool keys[]);
};
#endif
