#ifndef MINIENGINE3D_APPLICATION_H
#define MINIENGINE3D_APPLICATION_H

#include "Mesh.h"
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

    Mesh* testMesh;

    void initCube();
};


#endif
