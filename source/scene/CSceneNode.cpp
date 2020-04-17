#include "CSceneNode.h"
#include "IGameObject.h"

namespace magic
{
CSceneNode::CSceneNode(IGameObject *pGameObject)
:m_pGameObject(pGameObject)
{
}
CSceneNode::~CSceneNode()
{
}
void CSceneNode::Update()
{
    m_pGameObject->Update();
    for (int i=0; i<m_SceneNodeList.size(); ++i)
    {
        m_SceneNodeList[i]->Update();
    }
}

void CSceneNode::AddChild(ISceneNode *pChild)
{
    m_SceneNodeList.push_back(pChild);
}

void CSceneNode::AddParent(ISceneNode *pParent)
{
    pParent->AddChild(this);
}

} // namespace magic
