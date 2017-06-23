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
#include <explicit_euler.h>
#include <constant_force.h>
#include <physics_entity.h>
#include <model.h>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow*,double xpos, double ypos);
void ScrollCallback(GLFWwindow*,double xoffset, double yoffset);
void DoMovement();

const GLuint WIDTH = 800, HEIGHT = 600;

Camera camera(Vector3Gf(13.0f,0.0f,73.0f));

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

    Sphere sphere(1.0f, Vector3Gf(0.0f,0.0f,0.0f));

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

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());        
       
        GLuint VAO = sphere.GetMesh().GetVAO();

        Eigen::Matrix<float,4,4> model_matrix = sphere.GetModelMatrix();

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model_matrix.data());

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 2*sphere.GetMesh().GetNumEdges(), GL_UNSIGNED_INT,0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }    

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
