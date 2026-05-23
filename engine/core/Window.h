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
    static void pollEvents();

    GLFWwindow* getNativeWindow() const;

private:
    GLFWwindow* window;
};


#endif //MINIENGINE3D_WINDOW_H
