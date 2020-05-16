#include "CResourceManager.h"
#include "base/StringHelper.h"
#include "CTGAImage.h"
#include "resource/CShader.h"
#include "resource/CMesh.h"
#include "resource/CMaterial.h"

#include "FileWrapper.h"

namespace magic
{

IResource *CResourceManager::LoadResource(const char *fileName, EResourceType type)
{
#ifdef __APPLE__
    fileName = GetFileName(fileName).c_str();
    fileName = GetBundleFileName(fileName);
#endif
    switch (type)
    {
    case EResourceType::Image:
        return LoadImage(fileName);
    case EResourceType::Shader:
        return LoadShader(fileName);
    case EResourceType::Material:
        return LoadMaterial(fileName);
    case EResourceType::Mesh:
        return LoadMesh(fileName);
    case EResourceType::Model:
        return LoadModel(fileName);
    default:
        break;
    }
    return nullptr;
}

void CResourceManager::UnloadResource(IResource *pResource)
{
    if (pResource)
        delete pResource;
}

IResource *CResourceManager::LoadImage(const char *fileName)
{
    std::string extName = GetFileExtName(fileName);
    if (extName == "tga")
    {
        CTGAImage *pImage = new CTGAImage();
        pImage->Load(fileName);
        return pImage;
    }
    return nullptr;
}

IResource *CResourceManager::LoadShader(const char *fileName)
{
    std::string extName = GetFileExtName(fileName);
    if (extName == "vert")
    {
        return new CShader(EShaderType::Vertex, fileName);
    }
    else if (extName == "frag")
    {
        return new CShader(EShaderType::Fragment, fileName);
    }
    return nullptr;
}

IResource *CResourceManager::LoadMaterial(const char *fileName)
{
    return new CMaterial(this, fileName);
}

IResource *CResourceManager::LoadMesh(const char *fileName)
{
    return new CMesh(fileName);
}

IResource *CResourceManager::LoadModel(const char *fileName)
{
    return nullptr;
}

}
