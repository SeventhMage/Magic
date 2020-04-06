#ifndef _MAGIC_I_GAMEOBJECT_H_
#define _MAGIC_I_GAMEOBJECT_H_

#include "IObject.h"
#include "ISceneNode.h"
#include "component/IComponent.h"

#include <map>


namespace magic
{
class IGameObject : public IObject
{
public:
    virtual ~IGameObject()
    {
        for (auto it : m_ComponetMap)
        {
            if (it.second)
                delete it.second;
        }
    }
    IComponent *AddComponent();
        template <typename T>
    T *AddComponent()
    {
        T *com = new T();
        m_ComponetMap.insert(std::pair<int, CComponent *>(com->GetID(), com));
        return com;
    }

    template <typename T>
    void RemoveComponent(T *com)
    {
        if (com)
        {
            int id = com->GetID();
            m_ComponetMap.erase(id);
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

    virtual ISceneNode *GetSceneNode() const = 0;

    virtual void Update()
    {
        for (auto comIt : m_ComponetMap)
        {
            if (comIt.second)
                comIt.second->Update();
        }
    }

private:
    std::map<int, IComponent *> m_ComponetMap;
};
}

#endif