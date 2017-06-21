 #pragma once
#ifndef CAMERA_H
#define CAMERA_H
// Std. Includes
#include <vector>
#include <GL/glew.h>
#include <Eigen/Core>
#include <Eigen/Geometry> 
#include <look_at.h>
#include <vector3G.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
/**
    \brief A Camera is used to view a scene from a particular vantage point

    A Camera requires a position,orientation, and direction to look  in space. These things together define a camera centered coordinate system.
    This camera system is based on the camera system from <a href="https://learnopengl.com/#!Getting-started/Camera">here</a>
**/
class Camera
{
public:
    // Camera Attributes
    Vector3Gf m_position;
    Vector3Gf m_front;
    Vector3Gf m_up;
    Vector3Gf m_right;
    Vector3Gf m_world_up;
    // Eular Angles
    GLfloat m_yaw;
    GLfloat m_pitch;
    // Camera options
    GLfloat m_movement_speed;
    GLfloat m_mouse_sensitivity;
    GLfloat m_zoom;

    /**
        Constructs a Camera
        @param position position of the camera in world coordinates
        @param up up direction in world cordinates for the camera. This is used to define up in the Camera coordinate system
        @param yaw yaw value for the camera
        @param pitch pitch value for the camera
    **/
    Camera(Vector3Gf position = Vector3Gf(0.0f, 0.0f, 0.0f), Vector3Gf up = Vector3Gf(0.0f, 1.0f, 0.0f), GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);
   
    /** 
        @return the view matrix calculated using Eular Angles and the LookAt Matrix
    **/
    Eigen::Matrix<GLfloat,4,4> GetViewMatrix();

    /**
        Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM
        @param direction direction to move the camera in
        @param deltaTime time in seconds between rendering cycles. Helps smooth camera movement
    **/
    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

    /**
        Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        @param xoffset change in x position of mouse
        @param yoffset change in y position of mouse
        @param constrainPitch controls if pitch is constrained within [-89,89] degrees
    **/
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

    /**
        Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        @param yoffset change in scroll value
    **/
    void ProcessMouseScroll(GLfloat yoffset);

private:
    /** 
        Calculates the front vector from the Camera's (updated) Eular Angles
    **/
    void UpdateCameraVectors();
};
#endif
