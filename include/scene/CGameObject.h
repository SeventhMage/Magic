#ifndef _MAGIC_I_GAME_OBJECT_H_
#define _MAGIC_I_GAME_OBJECT_H_

#include "IObject.h"
#include "component/IComponent.h"
#include "ISceneNode.h"

#include <map>

namespace magic
{
class CGameObject : public IObject
{
public:
    CGameObject();
    ~CGameObject();
    template <typename T>
    T *AddComponent()
    {
        T *com = new T();
        m_ComponetMap.insert(std::pair<int, IComponent *>(com->GetID(), com));
        return com;
    }

    template <typename T>
    void RemoveComponent(T *com)
    {
        if (com)
        {
            int id = com->GetID();
            m_ComponetMap.erase(id)
        }
    }

    template <typename T>
    T *GetComponent(int id)
    {
        auto it = m_ComponetMap.find(id);
        if (it != m_ComponetMap.end())
        {
            return *it;
        }
        return nullptr;
    }

    ISceneNode *GetSceneNode() { return m_pSceneNode; }

    void Update();

private:
    std::map<int, IComponent *> m_ComponetMap;
    ISceneNode *m_pSceneNode;
};
} // namespace magic

#endif