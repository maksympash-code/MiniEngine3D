
#include "Camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


Camera::Camera()
:   position(0.0f, 0.0f, 3.0f),
    front(0.0f, 0.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f),
    fov(45.0f),
    nearPlane(0.1f),
    farPlane(100.0f) {
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(
        glm::radians(fov),
        aspectRatio,
        nearPlane,
        farPlane);
}

void Camera::setPosition(glm::vec3& newPosition) {
    position = newPosition;
}

const glm::vec3& Camera::getPosition() const {
    return position;
}