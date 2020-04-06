#ifndef _MAGIC_I_GAME_OBJECT_H_
#define _MAGIC_I_GAME_OBJECT_H_

#include "scene/IGameObject.h"

namespace magic
{
class CGameObject : public IGameObject
{
public:
    CGameObject();
    ~CGameObject();

    virtual OID GetID() const;
    virtual ISceneNode *GetSceneNode() const { return m_pSceneNode; }

    void Update();
private:
    ISceneNode *m_pSceneNode;
    OID m_OID;
};
} // namespace magic

#endif