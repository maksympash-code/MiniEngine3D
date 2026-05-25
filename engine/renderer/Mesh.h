
#ifndef MINIENGINE3D_MESH_H
#define MINIENGINE3D_MESH_H
#include <vector>


class Mesh {
public:
    Mesh(const std::vector<float>& vertices);
    ~Mesh();

    void draw() const;

private:
    unsigned int VAO, VBO;

    int vertexCount;
};


#endif //MINIENGINE3D_MESH_H
