#ifndef _MAGIC_C_COMPONENT_H_
#define _MAGIC_C_COMPONENT_H_

#include "IComponent.h"
#include "scene/CGameObject.h"

namespace magic
{
class CComponent : public IComponent
{
public:
    CComponent();
    virtual ~CComponent(){}
    virtual void Update();
    virtual void FixedUpdate();
    CGameObject *GetGameObject() { return m_pGameObject; }
    void SetGameObject(CGameObject *pGameObject) { m_pGameObject = pGameObject; }
private:
    CGameObject *m_pGameObject;
};
} // namespace magic

#endif
