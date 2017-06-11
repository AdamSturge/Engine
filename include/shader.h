
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#ifndef SHADER_H
#define SHADER_H
/**
    Wrapper around OpenGL vertex and fragment shaders
**/
class Shader
{
    public:
        GLuint Program;

        /**
            Creates a Shader that loads GLSL files from the supplied path
            @param vertexPath path to GLSL file that compiles into the vertex shader
            @param fragmentPath path to the GLSL file that compiles into the fragment shader
        **/
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        /**
            Loads the shader for rendering
        **/
        void Use();
};


#endif
