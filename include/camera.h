 #pragma once
#ifndef CAMERA_H
#define CAMERA_H
// Std. Includes
#include <vector>

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

// Default camera values
const GLfloat YAW        = -90.0f;
const GLfloat PITCH      =  0.0f;
const GLfloat SPEED      =  3.0f;
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;


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
    Vector3Gf Position;
    Vector3Gf Front;
    Vector3Gf Up;
    Vector3Gf Right;
    Vector3Gf WorldUp;
    // Eular Angles
    GLfloat Yaw;
    GLfloat Pitch;
    // Camera options
    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

    /**
        Constructs a Camera
        @param position position of the camera in world coordinates
        @param up up direction in world cordinates for the camera. This is used to define up in the Camera coordinate system
        @param yaw yaw value for the camera
        @param pitch pitch value for the camera
    **/
    Camera(Vector3Gf position = Vector3Gf(0.0f, 0.0f, 0.0f), Vector3Gf up = Vector3Gf(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(Vector3Gf(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
    {
        this->Position = position;
        this->WorldUp = up;
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }
   
    /** 
        @return the view matrix calculated using Eular Angles and the LookAt Matrix
    **/
    Eigen::Matrix<GLfloat,4,4> GetViewMatrix()
    {
	Eigen::Matrix<GLfloat,3,1> center = this->Position + this->Front;        
	return LookAt(this->Position, center, this->Up);
    }

    /**
        Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM
        @param direction direction to move the camera in
        @param deltaTime time in seconds between rendering cycles. Helps smooth camera movement
    **/
    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
    {
        GLfloat velocity = this->MovementSpeed * deltaTime;
        if (direction == FORWARD)
            this->Position += this->Front * velocity;
        if (direction == BACKWARD)
            this->Position -= this->Front * velocity;
        if (direction == LEFT)
            this->Position -= this->Right * velocity;
        if (direction == RIGHT)
            this->Position += this->Right * velocity;
    }

    /**
        Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        @param xoffset change in x position of mouse
        @param yoffset change in y position of mouse
        @param constrainPitch controls if pitch is constrained within [-89,89] degrees
    **/
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= this->MouseSensitivity;
        yoffset *= this->MouseSensitivity;

        this->Yaw   += xoffset;
        this->Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (this->Pitch > 89.0f)
                this->Pitch = 89.0f;
            if (this->Pitch < -89.0f)
                this->Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Eular angles
        this->updateCameraVectors();
    }

    /**
        Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        @param yoffset change in scroll value
    **/
    void ProcessMouseScroll(GLfloat yoffset)
    {
        if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
            this->Zoom -= yoffset;
        if (this->Zoom <= 1.0f)
            this->Zoom = 1.0f;
        if (this->Zoom >= 45.0f)
            this->Zoom = 45.0f;
    }

private:
    /** 
        Calculates the front vector from the Camera's (updated) Eular Angles
    **/
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        Vector3Gf front;
        front(0) = cos((M_PI/180.0)*(this->Yaw)) * cos((M_PI/180.0)*(this->Pitch));
        front(1) = sin((M_PI/180.0)*(this->Pitch));
        front(2) = sin((M_PI/180.0)*(this->Yaw)) * cos((M_PI/180.0)*(this->Pitch));
        this->Front = front.normalized();
        // Also re-calculate the Right and Up vector
        this->Right = this->Front.cross(this->WorldUp).normalized();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        this->Up    = this->Right.cross(this->Front).normalized();
    }
};
#endif
