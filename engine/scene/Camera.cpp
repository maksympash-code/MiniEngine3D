
#include "Camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


Camera::Camera()
:     position(0.0f, 0.0f, 3.0f),
      front(0.0f, 0.0f, -1.0f),
      up(0.0f, 1.0f, 0.0f),
      right(1.0f, 0.0f, 0.0f),
      worldUp(0.0f, 1.0f, 0.0f),
      yaw(-90.0f),
      pitch(0.0f),
      movementSpeed(1.5f),
      mouseSensitivity(0.05f),
      fov(45.0f),
      nearPlane(0.1f),
      farPlane(100.0f) {
    updateCameraVectors();
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

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    if (direction == CameraMovement::Forward) {
        position += front * velocity;
    }

    if (direction == CameraMovement::Backward) {
        position -= front * velocity;
    }

    if (direction == CameraMovement::Left) {
        position -= right * velocity;
    }

    if (direction == CameraMovement::Right) {
        position += right * velocity;
    }

    if (direction == CameraMovement::Up) {
        position += worldUp * velocity;
    }

    if (direction == CameraMovement::Down) {
        position -= worldUp * velocity;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }

    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
}

const glm::vec3& Camera::getPosition() const {
    return position;
}

void Camera::updateCameraVectors() {
    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}