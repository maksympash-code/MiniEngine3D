#ifndef MINIENGINE3D_WINDOW_H
#define MINIENGINE3D_WINDOW_H
#include <string>

struct GLFWwindow;

class Window {
    public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();

    bool isValid() const;

    GLFWwindow* getNativeWindow() const;
    float getAspectRatio() const;

private:
    GLFWwindow* window;
};


#endif //MINIENGINE3D_WINDOW_H
