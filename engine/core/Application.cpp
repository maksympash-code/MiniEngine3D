#include "Application.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../renderer/Shader.h"

Application::Application()
    : window(1280, 720, "MiniEngine3D"),
    shader(nullptr),
    VAO(0),
    VBO(0)
{
    if (window.isValid()) {
        shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
        initTriangle();
    }
}

Application::~Application() {
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }

    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }

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

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window.swapBuffers();
        window.pollEvents();
    }
}

void Application::initTriangle() {
    float vertices[] = {
        0.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         0.5f,  1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
        );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
