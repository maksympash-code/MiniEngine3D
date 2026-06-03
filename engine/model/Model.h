
#ifndef MINIENGINE3D_MODEL_H
#define MINIENGINE3D_MODEL_H
#include "Mesh.h"


class Model {
public:
    void addMesh(std::unique_ptr<Mesh> mesh);
    void draw() const;

private:
    std::vector<std::unique_ptr<Mesh>> meshes;
};


#endif //MINIENGINE3D_MODEL_H
