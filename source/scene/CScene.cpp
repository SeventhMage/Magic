#include "CScene.h"
#include "CSceneNode.h"

namespace magic
{
static OID s_SceneCount = 0;
CScene::CScene()
:m_pRootNode(new CSceneNode())
,m_SceneID(++s_SceneCount)
{
}

CScene::~CScene()
{
    SAFE_DEL(m_pRootNode);
}

void CScene::Update()
{
    m_pRootNode->Update();
}

} // namespace magic
