#ifndef MINIENGINE3D_SHADER_H
#define MINIENGINE3D_SHADER_H
#include <string>


class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;

    unsigned int getId() const;

private:
    unsigned int id;

    static std::string readFile(const std::string& path);
    static unsigned int compileShader(unsigned int type, const std::string& source);
};


#endif //MINIENGINE3D_SHADER_H
