
#ifndef MINIENGINE3D_MATERIAL_H
#define MINIENGINE3D_MATERIAL_H
#include "glm/vec3.hpp"

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

#endif //MINIENGINE3D_MATERIAL_H
