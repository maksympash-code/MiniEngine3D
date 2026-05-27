
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
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices);
    ~Mesh();

    void draw() const;

private:
    unsigned int VAO, VBO, EBO;

    int vertexCount;
    int indexCount;

    bool useIndices;
};


#endif //MINIENGINE3D_MESH_H
