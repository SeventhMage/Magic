#ifndef _MAGIC_ISCENE_NODE_H_
#define _MAGIC_ISCENE_NODE_H_

#include "math/CMatrix4.h"

namespace magic
{
class ISceneNode
{
public:
    virtual ~ISceneNode() {}
    virtual void Update() = 0;
    virtual void AddChild(ISceneNode *) = 0;
    virtual void AddParent(ISceneNode *) = 0;
    virtual CMatrix4 &GetAbsoluteTransform() = 0;
    virtual CMatrix4 &GetRelativeTransform() = 0;
};
} // namespace magic

#endif
