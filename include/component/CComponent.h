#ifndef _MAGIC_C_COMPONENT_H_
#define _MAGIC_C_COMPONENT_H_

#include "CObject.h"

namespace magic
{
class CComponent : public CObject
{
public:
    CComponent();
    virtual ~CComponent(){}
    virtual void Update();
    virtual void FixedUpdate();
};
} // namespace magic

#endif