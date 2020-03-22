#include "scene/CScene.h"

namespace magic
{
CScene::CScene()
{
}

CScene::~CScene()
{
    for (auto it : m_GameObjectMap)
    {
        if (it.second)
            delete it.second;
    }
}

void CScene::Update()
{
    for (auto it : m_GameObjectMap)
    {
        if (it.second)
        {
            it.second->Update();
        }
    }
}

} // namespace magic