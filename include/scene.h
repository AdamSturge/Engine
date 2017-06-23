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
/**
    \brief A scene in the engine

    A scene contains (pointers to) a number of PhysicsEntity objects to simululate and a number of Model objects to render.
**/
class Scene
{
    private:    
	std::vector<std::shared_ptr<PhysicsEntity>> m_physics_entity_ptrs;
	std::vector<std::shared_ptr<Model>> m_model_ptrs;
        std::shared_ptr<TimeIntegrator> m_time_integrator;
        ConstantForceGenerator m_constant_force_generator;
           
       
        /**
            Computes the net force acting on an entity
            @param entity_ptr pointer to the entity the forces are acting on
            @param force force vector that will be modified to contain the net force
        **/
        void ComputeNetForce(const std::shared_ptr<PhysicsEntity> entity_ptr, Vector3Gf &force);

    public :
        /**
            Creates a Scene instance with default values for its TimeIntegrator and ForceGenerator members
        **/
        Scene();

        /**
            Creates a Scene instance with the provided TimeIntegrator and ForceGenerator members
            @param integrator TimeIngrator instance to handle time evolution of the PhysicsEntities in the scene
            @param cfg  ConstantForceGenerator used to generate a spatially and temporally uniform force
        **/
        Scene(std::shared_ptr<TimeIntegrator> integrator, ConstantForceGenerator cfg);
        
        /**
            Add a PhysicsEntity to the Scene.
            @param entity_ptr a shared pointer to the PhysicsEntity to be added to the scene
        **/
        void AddPhysicsEntity(std::shared_ptr<PhysicsEntity> entity_ptr);

        /**
            Loads the PhysicsEntity at the given index into the supplied shared pointer
            @param index index into the PhysicsEntity list for this Scene
            @param entity_ptr pointer that will be modified to point to the PhysicsEntity at the given index
        **/
        void GetPhysicsEntity(const GLuint index, std::shared_ptr<PhysicsEntity> &entity_ptr);

        /**
            Adds a Model to the scene
            @param model_ptr a shared pointer to the model to be added to the scene
        **/
	void AddModel(std::shared_ptr<Model> model_ptr);

        /**
            Loads the Model at the given index into the supplied shared pointer
            @param index index into the Model list for this Scene
            @param model_ptr pointer that will be modifed to point to the Model at the given index
            @param VAO uint that will be modifed to store the vertex array object id for the Model
        **/
        void GetModel(const GLuint index, std::shared_ptr<Model> &model_ptr, GLuint &VAO);

        /**
            @return The number of Physics Entites in the Scene
        **/
        GLuint GetPhysicsEntityCount();

        /**
            @return The number of Models in the Scene
        **/
	GLuint GetModelCount();

        /**
            Moves the physical simulation one time step forward
        **/
        void StepPhysics();
 
        /**
            Renders the Models in the Scene to the screen
        **/
        void Render(Shader shader);

        /**
            Removes all Model data from the GPU
        **/
	void CleanUp();
};
#endif
