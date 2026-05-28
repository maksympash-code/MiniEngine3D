
#ifndef MINIENGINE3D_TRANSFORM_H
#define MINIENGINE3D_TRANSFORM_H
#include "glm/glm.hpp"


class Transform {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform();

    glm::mat4 getMatrix() const;
};


#endif //MINIENGINE3D_TRANSFORM_H
