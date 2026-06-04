
#ifndef MINIENGINE3D_POINTLIGHT_H
#define MINIENGINE3D_POINTLIGHT_H
#include "glm/vec3.hpp"

struct PointLight {
    glm::vec3 position;
    glm::vec3 color;

    float constant;
    float linear;
    float quadratic;
};

#endif //MINIENGINE3D_POINTLIGHT_H
