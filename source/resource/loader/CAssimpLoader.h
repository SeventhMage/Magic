#ifndef _MAGIC_C_ASSIMP_LOADER_H_
#define _MAGIC_C_ASSIMP_LOADER_H_

#include "resource/IModel.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <string>

namespace magic
{
class CAssimpLoader
{
public:
    bool Load(std::string path, IModel *pModel);
private:
    void processNode(aiNode* node, const aiScene* scene);
    IMesh *processMesh(aiMesh* mesh, const aiScene* scene);
    void loadMaterialTextures(aiMaterial* mat, aiTextureType type);
private:
    std::string directory;
    IModel *model;
};
}

#endif
