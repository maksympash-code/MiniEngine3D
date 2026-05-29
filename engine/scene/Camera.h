
#ifndef MINIENGINE3D_CAMERA_H
#define MINIENGINE3D_CAMERA_H
#include <glm/glm.hpp>


class Camera {
public:
    Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void setPosition(glm::vec3& position);
    const glm::vec3& getPosition() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float fov;
    float nearPlane;
    float farPlane;
};


#endif //MINIENGINE3D_CAMERA_H
