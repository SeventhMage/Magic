#ifndef _MAGIC_C_COMPONENT_H_
#define _MAGIC_C_COMPONENT_H_

#include "IObject.h"
#include "IComponent.h"

namespace magic
{
class CComponent : public IComponent
{
public:
    CComponent();
    virtual ~CComponent(){}
    virtual void Update();
    virtual void FixedUpdate();
};
} // namespace magic

#endif