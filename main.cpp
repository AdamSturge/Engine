#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <iostream>

const GLuint WIDTH = 800, HEIGHT = 600;

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

    glClearColor(0.2f,0.3f,0.3f,0.1f);

    // Uncomment to capture the mouse in the engine window
    //glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while(!glfwWindowShouldClose(window))
    {
   
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);     

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        glfwSwapBuffers(window);
    }    

    glfwTerminate();

    return 0;

}

