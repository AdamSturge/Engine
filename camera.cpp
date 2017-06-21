#include <camera.h>
/*
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
*/
Camera::Camera(Vector3Gf position, Vector3Gf up, GLfloat yaw, GLfloat pitch) : m_front(Vector3Gf(0.0f, 0.0f, -1.0f)), m_movement_speed(3.0f), m_mouse_sensitivity(0.25f), m_zoom(45.0f)
{
    this->m_position = position;
    this->m_world_up = up;
    this->m_yaw = yaw;
    this->m_pitch = pitch;
    this->UpdateCameraVectors();
}

Eigen::Matrix<GLfloat,4,4> Camera::GetViewMatrix()
{
	Eigen::Matrix<GLfloat,3,1> center = this->m_position + this->m_front;        
	return LookAt(this->m_position, center, this->m_up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->m_movement_speed * deltaTime;
    if (direction == FORWARD)
        this->m_position += this->m_front * velocity;
    if (direction == BACKWARD)
        this->m_position -= this->m_front * velocity;
    if (direction == LEFT)
        this->m_position -= this->m_right * velocity;
    if (direction == RIGHT)
        this->m_position += this->m_right * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= this->m_mouse_sensitivity;
    yoffset *= this->m_mouse_sensitivity;

    this->m_yaw   += xoffset;
    this->m_pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (this->m_pitch > 89.0f)
            this->m_pitch = 89.0f;
        if (this->m_pitch < -89.0f)
            this->m_pitch = -89.0f;
    }

    // Update m_front, m_right and m_up Vectors using the updated Eular angles
    this->UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    if (this->m_zoom >= 1.0f && this->m_zoom <= 45.0f)
        this->m_zoom -= yoffset;
    if (this->m_zoom <= 1.0f)
        this->m_zoom = 1.0f;
    if (this->m_zoom >= 45.0f)
        this->m_zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
    // Calculate the new m_front vector
    Vector3Gf front;
    front(0) = cos((M_PI/180.0)*(this->m_yaw)) * cos((M_PI/180.0)*(this->m_pitch));
    front(1) = sin((M_PI/180.0)*(this->m_pitch));
    front(2) = sin((M_PI/180.0)*(this->m_yaw)) * cos((M_PI/180.0)*(this->m_pitch));
    this->m_front = front.normalized();
    // Also re-calculate the m_right and m_up vector
    this->m_right = this->m_front.cross(this->m_world_up).normalized();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->m_up    = this->m_right.cross(this->m_front).normalized();
}

