
#include "Model.h"

void Model::addMesh(std::unique_ptr<Mesh> mesh) {
    meshes.push_back(std::move(mesh));
}

void Model::draw() const {
    for (const auto& mesh : meshes) {
        mesh->draw();
    }
}
