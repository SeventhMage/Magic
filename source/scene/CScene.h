#ifndef _MAGIC_SCENE_CSCENE_H_
#define _MAGIC_SCENE_CSCENE_H_

#include "scene/IGameObject.h"
#include "scene/IScene.h"

#include <map>

namespace magic
{
class CScene : public IScene
{
public:
    CScene();
    ~CScene();
    virtual OID GetID() const {return m_SceneID; }
    virtual void Update();
    virtual IGameObject *GetRootGameObject() const { return m_RootObject; }

private:
    IGameObject *m_RootObject;
    OID m_SceneID;
};
} // namespace magic
#endif