#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <shader.h>
#include <SOIL/SOIL.h>
#include <algorithm>
#include <camera.h>
#include <sphere.h>
#include <scene.h>
#include <Eigen/Core>
#include <perspective.h>
#include <vector3G.h>
#include <memory.h>
#include <verlet.h>
#include <midpoint_method.h>
#include <backward_euler.h>
#include <symplectic_euler.h>
#include <physics_entity.h>
#include <model.h>
#include <net_force_accumulator.h>
#include <spring.h>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow*,double xpos, double ypos);
void ScrollCallback(GLFWwindow*,double xoffset, double yoffset);
void DoMovement();

const GLuint WIDTH = 800, HEIGHT = 600;

Camera camera(Vector3Gf(0.0f,0.0f,10.0f));

bool keys[1024] = {false};

GLfloat delta_time = 0.0f; // Time between current frame and last frame
GLfloat last_frame = 0.0f; // Time of last frame

GLfloat camera_last_x = WIDTH/2.0; //initial mouse position
GLfloat camera_last_y = HEIGHT/2.0; //initial mouse position
bool first_mouse = true;

int main()
{
    // Begin building window
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"ENGINE",nullptr,nullptr);
    if(window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
    }

    int width,height;
    glfwGetFramebufferSize(window,&width,&height);

    glViewport(0,0,width,height);

    glfwSetKeyCallback(window,KeyCallback);
    glClearColor(0.2f,0.3f,0.3f,0.1f);

    //glfwSetCursorPosCallback(window,MouseCallback);
    //glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetScrollCallback(window, ScrollCallback);

    Shader shader("./shaders/shader.vs","./shaders/shader.frag");

    std::shared_ptr<TimeIntegrator> time_integrator_ptr(new Verlet(0.01));
    NetForceAccumulator net_force_accumulator;
    //Vector3Gf g(0.0f,-9.81f,0.0f);
    //net_force_accumulator.AddConstantForce(g);
    net_force_accumulator.EnableGravity(false);
    net_force_accumulator.EnableDrag(false);
    Scene scene(time_integrator_ptr,net_force_accumulator);
    
    Material material1;
    material1.ambient = Vector3Gf(0.0f,0.0f,0.3f);
    material1.diffuse = Vector3Gf(0.0f,0.0f,0.7f);
    material1.specular = Vector3Gf(0.0f,0.0f,1.0f);
    material1.shininess = 32.0f;

    std::shared_ptr<Sphere> sphere1_ptr(new Sphere(1.0f, Vector3Gf(-2.0f,0.0f,0.0f), Vector3Gf(0.0f,0.0f,0.0f), 1.0f, material1));
    scene.AddPhysicsEntity(sphere1_ptr);
    scene.AddModel(sphere1_ptr);
    
    Material material2;
    material2.ambient = Vector3Gf(0.3f,0.0f,0.0f);
    material2.diffuse = Vector3Gf(0.7f,0.0f,0.0f);
    material2.specular = Vector3Gf(1.0f,0.0f,0.0f);
    material2.shininess = 32.0f;

    std::shared_ptr<Sphere> sphere2_ptr(new Sphere(1.0f, Vector3Gf(2.0f,0.0f,0.0f), Vector3Gf(0.0f,0.0f,0.0f), 1.0f, material2));
    scene.AddPhysicsEntity(sphere2_ptr);
    scene.AddModel(sphere2_ptr);

    Spring spring(1.0f,5.0f,sphere1_ptr,sphere2_ptr);
    scene.AddSpring(spring);
   
    Light light;
    light.position = Vector3Gf(0.0f,0.0f,0.0f);
    light.diffuse  = Vector3Gf(1.0f,1.0f,1.0f);
    light.ambient  = Vector3Gf(1.0f,1.0f,1.0f);
    light.specular = Vector3Gf(1.0f,1.0f,1.0f);
    scene.SetLight(light);

    bool start = true;
    while(!glfwWindowShouldClose(window))
    {
        GLfloat current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
    
        glfwPollEvents();
        DoMovement();   

        if(keys[GLFW_KEY_F])
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }

        if(keys[GLFW_KEY_G])
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); 
        }

        if(keys[GLFW_KEY_P])
        {
            start = !start;
        }

        glClear(GL_COLOR_BUFFER_BIT);     

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        shader.Use();

        Eigen::Matrix<GLfloat,4,4> view;
        view = camera.GetViewMatrix();
        
        Eigen::Matrix<GLfloat,4,4> projection;
        projection = perspective<GLfloat>(camera.m_zoom, ((GLfloat)WIDTH)/((GLfloat)HEIGHT), 0.1f, 100.0f);          
      
        GLint modelLoc = glGetUniformLocation(shader.Program, "model");
        GLint viewLoc = glGetUniformLocation(shader.Program, "view"); 
        GLint projectionLoc = glGetUniformLocation(shader.Program, "projection");
        GLint normalLoc = glGetUniformLocation(shader.Program, "normalMat");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
  
        if(start)
        {
            scene.StepPhysics();
        }
//        std::cout << (sphere2_ptr->GetPosition() - sphere1_ptr->GetPosition()).transpose() << std::endl;       

        scene.Render(shader, camera.m_position);

        glfwSwapBuffers(window);
        glBindVertexArray(0);
    }    

    scene.CleanUp();

    glfwTerminate();

    return 0;

}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
   
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)        
        {
            keys[key] = false;
        }
    } 
}
void MouseCallback(GLFWwindow*,double xpos, double ypos)
{
    if(first_mouse)
    {
        camera_last_x = xpos;
        camera_last_y = ypos;
        first_mouse = false;
    }

    GLfloat xoffset = xpos - camera_last_x;
    GLfloat yoffset = camera_last_y - ypos; //reversed since y-coordinates range from bottom to top
    camera_last_x = xpos;
    camera_last_y = ypos;

    GLfloat sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.ProcessMouseMovement(xoffset,yoffset);
}

void ScrollCallback(GLFWwindow*, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void DoMovement()
{
    // Camera controls
    GLfloat cameraSpeed = 5.0f*delta_time;
    if (keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD,delta_time);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD,delta_time);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT,delta_time);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT,delta_time);
}
