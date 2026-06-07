# MiniEngine3D

MiniEngine3D is a basic 3D renderer written in C++ using modern OpenGL 3.3 Core Profile.

The project demonstrates loading and rendering a 3D model from an `.obj` file, interactive camera movement, indexed rendering, and Phong lighting with a point light source.

## Features

- OpenGL 3.3 Core Profile
- GLFW window and input handling
- GLAD OpenGL loader
- GLM matrix and vector math
- Assimp-based `.obj` model loading
- Indexed rendering using EBO
- Vertex attributes:
    - position
    - normal
    - texture coordinates
- Perspective projection with `glm::perspective`
- Fly camera using `glm::lookAt`
- Keyboard and mouse camera control
- Phong lighting model
- Point light with distance attenuation
- Material structure:
    - ambient
    - diffuse
    - specular
    - shininess
- Normal transformation using normal matrix
- Back-face culling with CCW winding

## Controls

| Input | Action |
|---|---|
| W | Move forward |
| S | Move backward |
| A | Move left |
| D | Move right |
| Q | Move down |
| E | Move up |
| Mouse | Look around |
| Esc | Close application |

## Technologies

- C++
- OpenGL 3.3
- GLFW
- GLAD
- GLM
- Assimp
- CMake

## Project Structure

```text
MiniEngine3D/
├── app/
│   └── main.cpp
├── engine/
│   ├── core/
│   │   ├── Application.h
│   │   ├── Application.cpp
│   │   ├── Window.h
│   │   └── Window.cpp
│   ├── renderer/
│   │   ├── Shader.h
│   │   ├── Shader.cpp
│   │   ├── Mesh.h
│   │   ├── Mesh.cpp
│   │   └── Material.h
│   ├── scene/
│   │   ├── Camera.h
│   │   ├── Camera.cpp
│   │   ├── Transform.h
│   │   ├── Transform.cpp
│   │   └── PointLight.h
│   └── model/
│       ├── Model.h
│       ├── Model.cpp
│       ├── ModelLoader.h
│       └── ModelLoader.cpp
├── res/
│   ├── shaders/
│   │   ├── phong.vert
│   │   └── phong.frag
│   └── models/
│       └── cube.obj
├── external/
└── CMakeLists.txt