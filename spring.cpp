#include <spring.h>

std::atomic<GLint> Spring::next_id(0);

Spring::Spring()
{
    id = Spring::next_id++;
};

Spring::Spring(GLfloat k, GLfloat l0, std::shared_ptr<PhysicsEntity> entity1_ptr, std::shared_ptr<PhysicsEntity> entity2_ptr) : k(k), l0(l0), entity1_ptr(entity1_ptr), entity2_ptr(entity2_ptr)
{
    id = Spring::next_id++;
}
