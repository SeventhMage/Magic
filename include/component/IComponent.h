#ifndef _MAGIC_I_COMPONENT_H_
#define _MAGIC_I_COMPONENT_H_

#include "IObject.h"
#include "math/CMatrix4.h"

namespace magic
{
class IGameObject;
class IComponent : public IObject
{
public:
    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;
    virtual IGameObject *GetGameObject() const = 0;
    virtual void SetGameObject(IGameObject *pGameObject) = 0;
    virtual void OnTransformChanged(const CMatrix4 &absMat) = 0;
};
}

#endif
