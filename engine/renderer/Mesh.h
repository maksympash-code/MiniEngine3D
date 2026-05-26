
#ifndef MINIENGINE3D_MESH_H
#define MINIENGINE3D_MESH_H
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices);
    ~Mesh();

    void draw() const;

private:
    unsigned int VAO, VBO;

    int vertexCount;
};


#endif //MINIENGINE3D_MESH_H
