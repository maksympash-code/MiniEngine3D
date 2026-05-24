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

        engine/renderer/Shader.cpp
        engine/renderer/Shader.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
        engine/core
        engine/renderer
)

target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glfw
        glad
        glm
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()