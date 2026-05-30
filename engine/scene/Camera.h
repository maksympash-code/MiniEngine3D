
#ifndef MINIENGINE3D_CAMERA_H
#define MINIENGINE3D_CAMERA_H
#include <glm/glm.hpp>

enum class CameraMovement {
    Forward,
    Backward,
    Left,
    Right,
    Up,
    Down
};


class Camera {
public:
    Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset);

    void setPosition(glm::vec3& position);
    const glm::vec3& getPosition() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;

    float fov;
    float nearPlane;
    float farPlane;

    void updateCameraVectors();
};


#endif //MINIENGINE3D_CAMERA_H
