#ifndef _MAGIC_I_GAME_OBJECT_H_
#define _MAGIC_I_GAME_OBJECT_H_

#include "IGameObject.h"

namespace magic
{
class CGameObject : public IGameObject
{
public:
    CGameObject(ISceneNode *pNode = nullptr);
    ~CGameObject();

    virtual OID GetID() const { return m_OID; }
    virtual void SetSceneNode(ISceneNode *pSceneNode);
    virtual ISceneNode *GetSceneNode() const { return m_pSceneNode; }
    virtual void OnTransformChanged();
    void Update();
private:
    ISceneNode *m_pSceneNode;
    OID m_OID;
};
} // namespace magic

#endif
