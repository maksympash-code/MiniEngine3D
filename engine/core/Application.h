#ifndef MINIENGINE3D_APPLICATION_H
#define MINIENGINE3D_APPLICATION_H

#include "Model.h"
#include "Shader.h"
#include "Window.h"
#include "../scene/Camera.h"
#include "../scene/Transform.h"

#include <memory>

#include "Material.h"
#include "PointLight.h"


class Application {
public:
    Application();
    ~Application();

    void run();

private:
    Window window;

    Shader* shader;

    std::unique_ptr<Model> model;

    Transform modelTransform;
    Camera camera;

    Material material{};
    PointLight light{};

    float deltaTime;
    float lastFrameTime;

    bool firstMouse;
    double lastMouseX;
    double lastMouseY;

    void loadModel();

    void processInput();
    void processMouse();
};


#endif
