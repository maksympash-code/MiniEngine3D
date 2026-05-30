#include "Window.h"

#include <iostream>
#include <ostream>

#include "glad/glad.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const std::string &title)
    : window(nullptr)
{

    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error " << error << ": " << description << std::endl;
    });

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
        return;
    }

    int frameBufferWidth, frameBufferHeight;

    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

bool Window::shouldClose() const {
    return window == nullptr || glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    if (window) {
        glfwSwapBuffers(window);
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::isValid() const {
    return window != nullptr;
}

GLFWwindow *Window::getNativeWindow() const {
    return window;
}

float Window::getAspectRatio() const {
    int width;
    int height;

    glfwGetFramebufferSize(window, &width, &height);

    if (height == 0)
        return 1.0f;

    return static_cast<float>(width) / static_cast<float>(height);
}
