#ifndef _MAGIC_ISCENE_NODE_H_
#define _MAGIC_ISCENE_NODE_H_

#include "math/CMatrix4.h"

namespace magic
{
class IGameObject;
class ISceneNode
{
public:
    virtual ~ISceneNode() {}
    virtual void Update() = 0;
    virtual ISceneNode *CreateChildNode() = 0;
    virtual void DestroyChildNode(ISceneNode *) = 0;
    virtual void AddGameObject(IGameObject *) = 0;
    virtual void RemoveGameObject(IGameObject *) = 0;
    virtual void SetPosition(const CVector3 &position) = 0;
    virtual void SetRotation(const CVector3 &rotation) = 0;
    virtual void SetScale(const CVector3 &scale) = 0;
    virtual ISceneNode *GetParent() const = 0;
    virtual const CVector3 &GetPosition() const = 0;
    virtual CVector3 GetAbslutePosition() const = 0;
    virtual const CVector3 &GetRotation() const = 0;
    virtual const CVector3 &GetScale() const = 0;
    virtual const CMatrix4 &GetAbsluateTransform() const = 0;
    virtual CMatrix4 GetRelativeTransform() const = 0;
    virtual void UpdateAbsluateTransform() = 0;
    virtual void SetNeedUpdateTransform(bool bNeed) = 0;
};
} // namespace magic

#endif
