#ifndef _MAGIC_C_RESOURCE_MANAGER_H_
#define _MAGIC_C_RESOURCE_MANAGER_H_

#include "resource/IResourceManager.h"

namespace magic
{
class CResourceManager : public IResourceManager
{
public:
    virtual IResource *LoadResource(const char *fileName, EResourceType type);
private:
    IResource *LoadImage(const char *fileName);
};

}

#endif
