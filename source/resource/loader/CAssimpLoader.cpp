#include "CAssimpLoader.h"
#include "base/Log.h"
#include "base/magicType.h"
#include "resource/CMesh.h"

#include <vector>

namespace magic
{
bool CAssimpLoader::Load(std::string path, IModel *pModel)
{
    model = pModel;
    // Read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    // Check for errors
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        LogError("ERROR::ASSIMP:: %s\n", importer.GetErrorString());
        return false;
    }
    // Retrieve the directory path of the filepath
    this->directory = path.substr(0, path.find_last_of('/'));

    // Process ASSIMP's root node recursively
    this->processNode(scene->mRootNode, scene);
    return true;
}

void CAssimpLoader::processNode(aiNode* node, const aiScene* scene)
{
    // Process each mesh located at the current node
    for(uint i = 0; i < node->mNumMeshes; i++)
    {
        // The node object only contains indices to index the actual objects in the scene.
        // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->model->AddMesh(this->processMesh(mesh, scene));
    }
    // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(uint i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }

}

IMesh *CAssimpLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // Data to fill
    std::vector<CVector3> positions;
    std::vector<CVector3> normals;
    std::vector<CVector2> uvs;
    std::vector<ushort> indices;
    
    // Walk through each of the mesh's vertices
    for(uint i = 0; i < mesh->mNumVertices; i++)
    {
        //switch y and z
        // Positions
        positions.push_back(CVector3(mesh->mVertices[i].x, mesh->mVertices[i].z, mesh->mVertices[i].y));
        // Normals
        if (mesh->mNormals)
            normals.push_back(CVector3(mesh->mNormals[i].x, mesh->mNormals[i].z, mesh->mNormals[i].y));
        // Texture Coordinates
        if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
        {
            uvs.push_back(CVector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
        }
    }
    // Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(uint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for(uint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // Process materials
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // Diffuse: texture_diffuseN
        // Specular: texture_specularN
        // Normal: texture_normalN

        
        // 1. Diffuse maps
        this->loadMaterialTextures(material, aiTextureType_DIFFUSE);
        /*
        // 2. Specular maps
        std::vector<ITexture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        */
    }
    
    // Return a mesh object created from the extracted mesh data
    IMesh *pMesh = new CMesh();
    pMesh->SetPositions((float (*)[3])&positions[0], sizeof(CVector3) * positions.size());
    if (uvs.size() > 0)
        pMesh->SetUVs((float (*)[2])&uvs[0], (int)(sizeof(CVector2) * uvs.size()));
    pMesh->SetNormals((float (*)[3])&normals[0], sizeof(CVector3) * normals.size());
    pMesh->SetIndices(&indices[0], sizeof(ushort) * indices.size());
    return pMesh;
}


// Checks all material textures of a given type and loads the textures if they're not loaded yet.
// The required info is returned as a Texture struct.
void CAssimpLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
    /*
    std::vector<IImage> textures;
    for(uint i = 0; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(uint j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // If texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    */
}

}
