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
        shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
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

        glm::mat4 mvp = projection * view * model;

        shader->use();
        shader->setMat4("uMVP", mvp);

        testMesh->draw();

        window.swapBuffers();
        window.pollEvents();
    }
}

void Application::initCube() {
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f},        {1.0f, 0.0f, 0.0f}}, // 0
        {{ 0.5f, -0.5f, -0.5f},        {0.0f, 1.0f, 0.0f}}, // 1
        {{ 0.5f,  0.5f, -0.5f},        {0.0f, 0.0f, 1.0f}}, // 2
        {{-0.5f,  0.5f, -0.5f},        {1.0f, 1.0f, 0.0f}}, // 3

        {{-0.5f, -0.5f,  0.5f},        {1.0f, 0.0f, 1.0f}}, // 4
        {{ 0.5f, -0.5f,  0.5f},        {0.0f, 1.0f, 1.0f}}, // 5
        {{ 0.5f,  0.5f,  0.5f},        {1.0f, 1.0f, 1.0f}}, // 6
        {{-0.5f,  0.5f,  0.5f},        {0.2f, 0.2f, 0.2f}}  // 7
    };

    std::vector<unsigned int> indices = {
        // back face
        0, 1, 2,
        2, 3, 0,

        // front face
        4, 5, 6,
        6, 7, 4,

        // left face
        4, 7, 3,
        3, 0, 4,

        // right face
        1, 5, 6,
        6, 2, 1,

        // bottom face
        4, 5, 1,
        1, 0, 4,

        // top face
        3, 2, 6,
        6, 7, 3
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
