#ifndef SPRING_H
#define SPRING_H

#include <physics_entity.h>
#include <memory>
#include <atomic>
/**
    \brief data structure that represents a spring
**/
struct Spring
{
    private:
        static std::atomic<GLint> next_id;

    public :
        GLint id; // unique id for this spring
        GLfloat k; // stiffness coefficent
        GLfloat l0; // rest length
        std::shared_ptr<PhysicsEntity> entity1_ptr;
        std::shared_ptr<PhysicsEntity> entity2_ptr;

    /**
        Constructs a spring with default stiffness and rest length, and no entites on its endpoints
    **/
    Spring();
    
    /**
        Constucts a spring using the provided parameters
        @param k stiffness coefficent of the spring
        @param l0 rest length of the spring
        @param entity1_ptr pointer to entity on one end of the spring
        @param entity2_ptr pointer to entity on other end of the spring
    **/
    Spring(GLfloat k, GLfloat l0, std::shared_ptr<PhysicsEntity> entity1_ptr, std::shared_ptr<PhysicsEntity> entity2_ptr);
};
#endif
