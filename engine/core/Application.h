#ifndef MINIENGINE3D_APPLICATION_H
#define MINIENGINE3D_APPLICATION_H

#include "Shader.h"
#include "Window.h"


class Application {
public:
    Application();
    ~Application();

    void run();

private:
    Window window;

    Shader* shader;

    unsigned int VAO, VBO;

    void initTriangle();
};


#endif
