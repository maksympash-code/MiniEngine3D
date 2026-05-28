#include "Shader.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    : id(0) {
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cout << "Shader source is empty. Check shader paths." << std::endl;
        return;
    }

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(id, 1024, nullptr, infoLog);
        std::cout << "Failed to link shader program:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    if (id != 0) {
        glDeleteProgram(id);
    }
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) {
    int loction = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(loction, 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::getId() const {
    return id;
}

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source) {
    unsigned int shader = glCreateShader(type);

    const char* code = source.c_str();
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cout << "Failed to compile shader:\n" << infoLog << std::endl;
    }

    return shader;
}
