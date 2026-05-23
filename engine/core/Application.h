#ifndef MINIENGINE3D_APPLICATION_H
#define MINIENGINE3D_APPLICATION_H
#include "Window.h"


class Application {
public:
    Application();
    ~Application();

    void run();

private:
    Window window;
};


#endif
