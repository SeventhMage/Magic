#ifndef _MAGIC_C_RESOURCE_MANAGER_H_
#define _MAGIC_C_RESOURCE_MANAGER_H_

#include "resource/IResourceManager.h"

namespace magic
{
class CResourceManager : public IResourceManager
{
public:
    virtual IResource *LoadResource(const char *fileName, EResourceType type);
    virtual void UnloadResource(IResource *pResource);
private:
    IResource *LoadImage(const char *fileName);
    IResource *LoadShader(const char *fileName);
    IResource *LoadMaterial(const char *fileName);
    IResource *LoadMesh(const char *fileName);
    IResource *LoadModel(const char *fileName);
};

}

#endif
