#ifndef _MAGIC_C_SCENE_NODE_H_
#define _MAGIC_C_SCENE_NODE_H_

#include "scene/ISceneNode.h"

#include <vector>

namespace magic
{
class IGameObject;
class CSceneNode : public ISceneNode
{
public:
    CSceneNode(IGameObject *pGameObject);
    virtual ~CSceneNode();
    virtual void Update();
    virtual void AddChild(ISceneNode *pChild);
    virtual void AddParent(ISceneNode *pParent);
private:
    IGameObject *m_pGameObject;
    std::vector<ISceneNode *> m_SceneNodeList;
};
} // namespace magic

#endif
