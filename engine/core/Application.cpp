#include "Application.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>

#include "ModelLoader.h"
#include "Model.h"
#include "../renderer/Shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Application::Application()
    : window(1280, 720, "MiniEngine3D"),
    shader(nullptr),
    model(nullptr),
    deltaTime(0.0f),
    lastFrameTime(0.0f),
    firstMouse(true),
    lastMouseX(640.0),
    lastMouseY(360.0)
{
    if (window.isValid()) {
        shader = new Shader("res/shaders/phong.vert", "res/shaders/phong.frag");
        loadModel();

        material = {
            glm::vec3(0.24725f, 0.1995f, 0.0745f),
            glm::vec3(0.75164f, 0.60648f, 0.22648f),
            glm::vec3(0.628281f, 0.555802f, 0.366065f),
            32.0f
        };

        light = {
            glm::vec3(2.0f, 2.0f, 2.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            1.0f,
            0.09f,
            0.032f
        };

        glfwSetInputMode(window.getNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

Application::~Application() {
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

        // auto time = static_cast<float>(glfwGetTime());
        //
        // modelTransform.rotation.y = time * 50.0f;
        // modelTransform.rotation.x = time * 25.0f;

        float aspectRatio = window.getAspectRatio();

        glm::mat4 modelMatrix = modelTransform.getMatrix();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);


        shader->use();
        shader->setMat4("uModel", modelMatrix);
        shader->setMat4("uView", view);
        shader->setMat4("uProjection", projection);

        shader->setVec3("uViewPos", camera.getPosition());

        // Material: gold
        shader->setVec3("uMaterial.ambient",  material.ambient);
        shader->setVec3("uMaterial.diffuse",  material.diffuse);
        shader->setVec3("uMaterial.specular", material.specular);
        shader->setFloat("uMaterial.shininess", material.shininess);

        // Point light
        shader->setVec3("uLight.position", light.position);
        shader->setVec3("uLight.color", light.color);
        shader->setFloat("uLight.constant", light.constant);
        shader->setFloat("uLight.linear", light.linear);
        shader->setFloat("uLight.quadratic", light.quadratic);

        if (model) {
            model->draw();
        }


        window.swapBuffers();
        window.pollEvents();
    }
}

void Application::loadModel() {
    model = ModelLoader::loadModel("res/models/rocket.obj");

    if (!model) {
        std::cout << "Model was not loaded." << std::endl;
    }
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
