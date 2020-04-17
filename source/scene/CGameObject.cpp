#include "scene/CGameObject.h"
#include "CSceneNode.h"

namespace magic
{
static OID s_OIDCount;
CGameObject::CGameObject()
: m_pSceneNode(new CSceneNode(this))
, m_OID(++s_OIDCount)
{
}

CGameObject::~CGameObject()
{
    if (m_pSceneNode)
        delete m_pSceneNode;
}
void CGameObject::Update()
{
    IGameObject::Update();    
}

} // namespace magic
