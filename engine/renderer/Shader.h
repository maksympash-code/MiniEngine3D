#ifndef MINIENGINE3D_SHADER_H
#define MINIENGINE3D_SHADER_H
#include <string>

#include <glm/glm.hpp>


class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    void setMat4(const std::string& name, const glm::mat4& matrix) const;
    void setVec3(const std::string& name, const glm::vec3& vector) const;
    void setFloat(const std::string& name, float value) const;

    unsigned int getId() const;

private:
    unsigned int id;

    static std::string readFile(const std::string& path);
    static unsigned int compileShader(unsigned int type, const std::string& source);
};


#endif //MINIENGINE3D_SHADER_H
