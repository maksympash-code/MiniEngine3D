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
    testMesh(nullptr)
{
    if (window.isValid()) {
        shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
        initCube();
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
        if (glfwGetKey(window.getNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window.getNativeWindow(), true);
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = static_cast<float>(glfwGetTime());

        cubeTransform.rotation.y = time * 50.0f;
        cubeTransform.rotation.x = time * 25.0f;

        float aspectRatio = 1280.0f / 720.0f;

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
