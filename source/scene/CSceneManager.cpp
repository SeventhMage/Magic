#include "CSceneManager.h"
#include "CScene.h"

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

IScene *CSceneManager::LoadScene(const char *fileName)
{
    m_pScene = new CScene();
    return m_pScene;
}

IScene *CSceneManager::LoadScene()
{
    m_pScene = new CScene();
    return m_pScene;
}

void CSceneManager::UnloadScene()
{
    if (m_pScene)
    {
        delete m_pScene;
        m_pScene = nullptr;
    }
}

void CSceneManager::Update()
{
    if (m_pScene)
        m_pScene->Update();
}

void CSceneManager::FixedUpdate()
{
    
}

}
