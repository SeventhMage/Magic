#ifndef _MAGIC_I_RESOURCE_H_
#define _MAGIC_I_RESOURCE_H_

#include "IObject.h"

namespace magic
{
enum EResourceType
{
    Mesh,
    Material,
    Model,
    Shader,
};
class IResource : public IObject
{
public:
    virtual ~IResource();
    virtual EResourceType GetType() const = 0;
};
}
#endif