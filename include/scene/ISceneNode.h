#ifndef _MAGIC_ISCENE_NODE_H_
#define _MAGIC_ISCENE_NODE_H_

namespace magic
{
class ISceneNode
{
public:
    virtual ~ISceneNode() {}
    virtual void Update() = 0;
    virtual void AddChild(ISceneNode *) = 0;
    virtual void AddParent(ISceneNode *) = 0;
};
} // namespace magic

#endif