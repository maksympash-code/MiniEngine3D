cmake_minimum_required(VERSION 3.30)
project(MiniEngine3D)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_subdirectory(external)

add_executable(${PROJECT_NAME}
        app/main.cpp
        engine/core/Window.cpp
        engine/core/Window.h
        engine/core/Application.cpp
        engine/core/Application.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
        engine/core
)

target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glfw
        glad
        glm
)

if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()