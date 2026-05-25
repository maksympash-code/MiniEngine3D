#include "Application.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../renderer/Shader.h"

Application::Application()
    : window(1280, 720, "MiniEngine3D"),
    shader(nullptr),
    triangleMesh(nullptr)
{
    if (window.isValid()) {
        shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
        initTriangle();
    }
}

Application::~Application() {
    delete triangleMesh;
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

        shader->use();
        triangleMesh->draw();

        window.swapBuffers();
        window.pollEvents();
    }
}

void Application::initTriangle() {
    std::vector<float> vertices = {
        0.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         0.5f,  1.0f, 0.0f
    };

    triangleMesh = new Mesh(vertices);
}
