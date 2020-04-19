#ifndef _MAGIC_I_SCENE_H_
#define _MAGIC_I_SCENE_H_

#include "ISceneNode.h"
#include "IObject.h"

namespace magic
{
class IScene : public IObject
{
public:
    virtual ~IScene(){}
    virtual void Update() = 0;
    virtual ISceneNode *GetRootNode() const = 0;
};
}

#endif
