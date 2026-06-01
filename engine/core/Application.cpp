#include "Application.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../renderer/Shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Application::Application()
    : window(1280, 720, "MiniEngine3D"),
    shader(nullptr),
    testMesh(nullptr),
    deltaTime(0.0f),
    lastFrameTime(0.0f),
    firstMouse(true),
    lastMouseX(640.0),
    lastMouseY(360.0)
{
    if (window.isValid()) {
        shader = new Shader("res/shaders/phong.vert", "res/shaders/phong.frag");
        initCube();

        glfwSetInputMode(window.getNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

Application::~Application() {
    delete testMesh;
    delete shader;
}

void Application::run() {
    if (!window.isValid()) {
        return;
    }

    while (!window.shouldClose()) {
        auto currentFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        processInput();
        processMouse();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto time = static_cast<float>(glfwGetTime());

        cubeTransform.rotation.y = time * 50.0f;
        cubeTransform.rotation.x = time * 25.0f;

        float aspectRatio = window.getAspectRatio();

        glm::mat4 model = cubeTransform.getMatrix();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);


        shader->use();
        shader->setMat4("uModel", model);
        shader->setMat4("uView", view);
        shader->setMat4("uProjection", projection);

        shader->setVec3("uViewPos", camera.getPosition());

        // Material: gold
        shader->setVec3("uMaterial.ambient",  glm::vec3(0.24725f, 0.1995f, 0.0745f));
        shader->setVec3("uMaterial.diffuse",  glm::vec3(0.75164f, 0.60648f, 0.22648f));
        shader->setVec3("uMaterial.specular", glm::vec3(0.628281f, 0.555802f, 0.366065f));
        shader->setFloat("uMaterial.shininess", 32.0f);

        // Point light
        shader->setVec3("uLight.position", glm::vec3(2.0f, 2.0f, 2.0f));
        shader->setVec3("uLight.color", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setFloat("uLight.constant", 1.0f);
        shader->setFloat("uLight.linear", 0.09f);
        shader->setFloat("uLight.quadratic", 0.032f);

        testMesh->draw();

        window.swapBuffers();
        window.pollEvents();
    }
}

void Application::initCube() {
    std::vector<Vertex> vertices = {
        // Front face (+Z)
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        // Back face (-Z)
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

        // Left face (-X)
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        // Right face (+X)
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        // Top face (+Y)
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

        // Bottom face (-Y)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,    2, 3, 0,       // front
        4, 5, 6,    6, 7, 4,       // back
        8, 9, 10,   10, 11, 8,     // left
        12, 13, 14, 14, 15, 12,    // right
        16, 17, 18, 18, 19, 16,    // top
        20, 21, 22, 22, 23, 20     // bottom
    };

    testMesh = new Mesh(vertices, indices);
}


void Application::processInput() {
    GLFWwindow* nativeWindow = window.getNativeWindow();

    if (glfwGetKey(nativeWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(nativeWindow, true);
    }

    if (glfwGetKey(nativeWindow, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::Forward, deltaTime);
    }

    if (glfwGetKey(nativeWindow, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::Backward, deltaTime);
    }

    if (glfwGetKey(nativeWindow, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::Left, deltaTime);
    }

    if (glfwGetKey(nativeWindow, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::Right, deltaTime);
    }

    if (glfwGetKey(nativeWindow, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::Down, deltaTime);
    }

    if (glfwGetKey(nativeWindow, GLFW_KEY_E) == GLFW_PRESS) {
        camera.processKeyboard(CameraMovement::Up, deltaTime);
    }
}

void Application::processMouse() {
    double mouseX, mouseY;

    glfwGetCursorPos(window.getNativeWindow(), &mouseX, &mouseY);

    if (firstMouse) {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        firstMouse = false;
    }

    auto xOffset = static_cast<float>(mouseX - lastMouseX);
    auto yOffset = static_cast<float>(lastMouseY - mouseY);

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    camera.processMouseMovement(xOffset, yOffset);
}
