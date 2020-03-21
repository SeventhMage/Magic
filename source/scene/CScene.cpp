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

void CScene::Update(int delta)
{
}
void CScene::FixedUpdate(int delta)
{
}
void CScene::Render()
{
}
} // namespace magic