#include "scene/CGameObject.h"
#include "CSceneNode.h"

namespace magic
{
static OID s_OIDCount;
CGameObject::CGameObject(ISceneNode *pSceneNode)
: m_pSceneNode(pSceneNode)
, m_OID(++s_OIDCount)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::SetSceneNode(ISceneNode *pSceneNode)
{
    m_pSceneNode = pSceneNode;
    m_pSceneNode->AddGameObject(this);
}

void CGameObject::OnTransformChanged()
{
    for (auto it : m_ComponetMap)
    {
        it.second->OnTransformChanged(m_pSceneNode->GetAbsluateTransform());
    }
}

void CGameObject::Update()
{
    IGameObject::Update();    
}

} // namespace magic
