#ifndef _MAGIC_SCENE_CSCENE_H_
#define _MAGIC_SCENE_CSCENE_H_

#include "CGameObject.h"

#include <map>

namespace magic
{
class CScene
{
public:
    CScene();
    ~CScene();

    template<typename T>
    T *AddGameObject()
    {
        T *go = new T();
        m_GameObjectMap.insert(std::pair<int, CGameObject*>(go->GetID(), go));
        return go;
    }

    template<typename T>
    void RemoveGameObject(T *go)
    {
        if (go)
        {
            OID id = go->GetID();
            m_GameObjectMap.erase(id);
        }
    }

    void Update(int delta);
    void FixedUpdate(int delta);
    void Render();
private:
    std::map<OID, CGameObject *> m_GameObjectMap;
};
} // namespace magic
#endif