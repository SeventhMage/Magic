#ifndef _MAGIC_I_GAME_OBJECT_H_
#define _MAGIC_I_GAME_OBJECT_H_

#include "../IObject.h"
#include "../component/IComponent.h"

#include <map>

namespace magic
{
class CGameObject : public IObject
{
public:
    template <typename T>
    T *AddComponent()
    {
        int id = m_ComponetMap.count + 1;
        T *com = new T(id);
        m_ComponetMap.insert(std::pair<int, IComponent *>(id, com));
        return com;
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
private:
    std::map<int, IComponent *> m_ComponetMap;
};
}

#endif