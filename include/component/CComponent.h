#ifndef _MAGIC_C_COMPONENT_H_
#define _MAGIC_C_COMPONENT_H_

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
    virtual IGameObject *GetGameObject() const { return m_pGameObject; }
    virtual void SetGameObject(IGameObject *pGameObject) { m_pGameObject = pGameObject; }
    virtual void OnTransformChanged(const CMatrix4 &absMat) {}
protected:
    IGameObject *m_pGameObject;
};
} // namespace magic

#endif
