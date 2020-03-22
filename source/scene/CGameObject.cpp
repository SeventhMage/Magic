#include "scene/CGameObject.h"
#include "CSceneNode.h"

namespace magic
{
CGameObject::CGameObject()
    : m_pSceneNode(new CSceneNode())
{
}

CGameObject::~CGameObject()
{
    if (m_pSceneNode)
        delete m_pSceneNode;
    for (auto it : m_ComponetMap)
    {
        if (it.second)
            delete it.second;
    }
}
void CGameObject::Update()
{
    if (m_pSceneNode)
        m_pSceneNode->Update();
    for (auto comIt : m_ComponetMap)
    {
        if (comIt.second)
            comIt.second->Update();
    }
}

} // namespace magic