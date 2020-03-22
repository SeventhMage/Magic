#include "scene/CSceneManager.h"

namespace magic
{
CSceneManager::CSceneManager()
:m_pScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
    if (m_pScene)
        delete m_pScene;
}

CScene *CSceneManager::LoadScene(const char *fileName)
{
    m_pScene = new CScene();
    return m_pScene;
}

void CSceneManager::UnloadScene(CScene *scene)
{
    if (scene)
        delete scene;
}

void CSceneManager::Update()
{
    if (m_pScene)
        m_pScene->Update();
}

}