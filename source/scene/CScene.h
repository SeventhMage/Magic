#ifndef _MAGIC_SCENE_CSCENE_H_
#define _MAGIC_SCENE_CSCENE_H_

#include "scene/IScene.h"

#include <map>

namespace magic
{
class CScene : public IScene
{
public:
    CScene();
    ~CScene();
    virtual OID GetID() const { return m_SceneID; }
    virtual void Update();
    virtual ISceneNode *GetRootNode() const { return m_pRootNode; }

private:
    ISceneNode *m_pRootNode;
    OID m_SceneID;
};
} // namespace magic
#endif