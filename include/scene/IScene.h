#ifndef _MAGIC_I_SCENE_H_
#define _MAGIC_I_SCENE_H_

#include "IGameObject.h"

namespace magic
{
class IScene : public IObject
{
public:
    virtual ~IScene(){}
    virtual void Update() = 0;
    virtual IGameObject *GetRootGameObject() const = 0;
};
}

#endif