#ifndef _MAGIC_C_SCENE_NODE_H_
#define _MAGIC_C_SCENE_NODE_H_

#include "scene/ISceneNode.h"

#include <vector>

namespace magic
{
class CSceneNode : public ISceneNode
{
public:
    CSceneNode();
    virtual ~CSceneNode();
    virtual void Update();
    virtual ISceneNode *CreateChildNode();
    virtual void DestroyChildNode(ISceneNode *pNode);
    virtual void AddGameObject(IGameObject *pGameObject);
    virtual IGameObject *AddGameObject();
    virtual void RemoveGameObject(IGameObject *);
    virtual void SetPosition(const CVector3 &position);

    virtual ISceneNode *GetParent() const { return m_pParentNode; }
    virtual const CVector3 &GetPosition() const;

    virtual void SetRotation(const CVector3 &rotation);
    virtual const CVector3 &GetRotation() const;

    virtual CVector3 GetAbslutePosition() const;

    virtual void SetScale(const CVector3 &scale);

    virtual const CVector3 &GetScale() const;

    virtual const CMatrix4 &GetAbsluateTransform() const;
    virtual CMatrix4 GetRelativeTransform() const;
    virtual void SetRelativeTransform(const CMatrix4 &mat4);

    virtual void SetActive(bool bActive);
    virtual bool IsActive() const;

    virtual void UpdateRelateTransform();

    virtual void UpdateAbsluateTransform();
    virtual void SetNeedUpdateTransform(bool bNeed);

private:
    std::vector<IGameObject *> m_GameObjectList;
    std::vector<ISceneNode *> m_SceneNodeList;
    ISceneNode *m_pParentNode;
    CMatrix4 m_AbsoluteTransform;
    CMatrix4 m_RelativeTransform;
    CVector3 m_relativePosition;
    CVector3 m_relativeRotation;
    CVector3 m_relativeScale;
    bool m_bActive;
    bool m_bNeedUpdate;
    bool m_bUpdateRelative;
};
} // namespace magic

#endif
