#ifndef _MAGIC_I_COMPONENT_H_
#define _MAGIC_I_COMPONENT_H_

#include "IObject.h"

namespace magic
{
class IComponent : public IObject
{
public:
    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;
};
}

#endif