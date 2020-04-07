#include "CScene.h"
#include "CGameObject.h"

namespace magic
{
static OID s_SceneCount = 0;
CScene::CScene()
:m_RootObject(new CGameObject())
,m_SceneID(++s_SceneCount)
{
}

CScene::~CScene()
{
    
}

void CScene::Update()
{
    
}

} // namespace magic