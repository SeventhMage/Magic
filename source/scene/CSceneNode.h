#ifndef _MAGIC_C_SCENE_NODE_H_
#define _MAGIC_C_SCENE_NODE_H_

#include "scene/ISceneNode.h"

namespace magic
{
class CSceneNode : public ISceneNode
{
public:
    CSceneNode();
    virtual ~CSceneNode();
    virtual void Update();
};
} // namespace magic

#endif