
#ifndef MINIENGINE3D_MODELLOADER_H
#define MINIENGINE3D_MODELLOADER_H
#include <memory>
#include <string>

#include "Model.h"
#include "assimp/scene.h"


class ModelLoader {
public:
    static std::unique_ptr<Model> loadModel(const std::string& path);

private:
    static void processNode(aiNode* node, const aiScene* scene, Model& model);
    static std::unique_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
};


#endif //MINIENGINE3D_MODELLOADER_H
