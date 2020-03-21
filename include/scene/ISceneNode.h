#ifndef _MAGIC_SCENE_ISCENE_NODE_H_
#define _MAGIC_SCENE_ISCENE_NODE_H_

namespace magic
{
class ISceneNode
{
public:
    virtual ~ISceneNode() {}
    virtual void Update() = 0;
};
} // namespace magic

#endif