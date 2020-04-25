#ifndef _MAGIC_I_RESOURCE_MANAGER_H_
#define _MAGIC_I_RESOURCE_MANAGER_H_

#include "IResource.h"

namespace magic
{
class IResourceManager
{
public:
    virtual ~IResourceManager() {}
    virtual IResource *LoadResource(const char *fileName, EResourceType type) = 0;
};
}

#endif