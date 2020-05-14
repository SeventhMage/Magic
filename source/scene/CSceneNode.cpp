#include "CSceneNode.h"
#include "scene/IGameObject.h"

#include <algorithm>

namespace magic
{
CSceneNode::CSceneNode()
:m_pParentNode(nullptr)
,m_bActive(true)
,m_bNeedUpdate(true)
,m_bUpdateRelative(true)
,m_relativeScale(1.f, 1.f, 1.f)
{
}
CSceneNode::~CSceneNode()
{
    for (size_t i=0; i<m_SceneNodeList.size(); ++i)
        delete m_SceneNodeList[i];
}
void CSceneNode::Update()
{
    UpdateRelateTransform();
    UpdateAbsluateTransform();
    for (size_t i = 0; i < m_GameObjectList.size(); ++i)
    {
        m_GameObjectList[i]->Update();
    }
    for (size_t i = 0; i < m_SceneNodeList.size(); ++i)
    {
        m_SceneNodeList[i]->Update();
    }
}

ISceneNode *CSceneNode::CreateChildNode()
{
    CSceneNode *pNode = new CSceneNode();
    pNode->m_pParentNode = this;
    m_SceneNodeList.push_back(pNode);
    return pNode;
}

void CSceneNode::DestroyChildNode(ISceneNode *pNode)
{
    for (auto it = m_SceneNodeList.begin(); it != m_SceneNodeList.end(); ++it)
    {
        if (pNode == *it)
        {
            m_SceneNodeList.erase(it);
            delete pNode;
            break;
        }
    }
}

void CSceneNode::AddGameObject(IGameObject *pGameObject)
{
    if (std::find(m_GameObjectList.begin(), m_GameObjectList.end(), pGameObject) == m_GameObjectList.end())
    {    
        ISceneNode *pSrcNode = pGameObject->GetSceneNode();
        if (pSrcNode)
            pSrcNode->RemoveGameObject(pGameObject);
        m_GameObjectList.push_back(pGameObject);
    }
}

void CSceneNode::RemoveGameObject(IGameObject *pGameObject)
{
    auto it = std::find(m_GameObjectList.begin(), m_GameObjectList.end(), pGameObject);
    if (it != m_GameObjectList.end())
    {
        m_GameObjectList.erase(it);
    }
}

void CSceneNode::SetPosition(const CVector3 &position)
{
    m_relativePosition = position;
    SetNeedUpdateTransform(true);
}

const CVector3 &CSceneNode::GetPosition() const
{
    return m_relativePosition;
}

void CSceneNode::SetRotation(const CVector3 &rotation)
{
    m_relativeRotation = rotation;
    SetNeedUpdateTransform(true);
}

const CVector3 &CSceneNode::GetRotation() const
{
    return m_relativeRotation;
}

CVector3 CSceneNode::GetAbslutePosition() const
{
    return m_AbsoluteTransform.GetTranslation();
}

void CSceneNode::SetScale(const CVector3 &scale)
{
    m_relativeScale = scale;
    SetNeedUpdateTransform(true);
}

const CVector3 &CSceneNode::GetScale() const
{
    return m_relativeScale;
}

const CMatrix4 &CSceneNode::GetAbsluateTransform() const
{
    return m_AbsoluteTransform;
}

CMatrix4 CSceneNode::GetRelativeTransform() const
{
    return m_RelativeTransform;
}

void CSceneNode::SetActive(bool bActive)
{
    m_bActive = bActive;
}

bool CSceneNode::IsActive() const
{
    return m_bActive;
}

void CSceneNode::UpdateAbsluateTransform()
{
    if (m_bNeedUpdate)
    {
        if (m_pParentNode)
        {
            m_AbsoluteTransform = GetRelativeTransform() * m_pParentNode->GetAbsluateTransform();
        }
        else
        {
            m_AbsoluteTransform = GetRelativeTransform();
        }

        for (size_t i = 0; i<m_GameObjectList.size(); ++i)
            m_GameObjectList[i]->OnTransformChanged();
        m_bNeedUpdate = false;
    }
}

void CSceneNode::SetNeedUpdateTransform(bool bNeed)
{
    m_bNeedUpdate = bNeed;
    m_bUpdateRelative = bNeed;
    for (auto it = m_SceneNodeList.begin(); it != m_SceneNodeList.end(); ++it)
    {
        (*it)->SetNeedUpdateTransform(bNeed);
    }
}

void CSceneNode::UpdateRelateTransform()
{
    if (m_bUpdateRelative)
    {
        CMatrix4 mat;

        mat.SetTranslation(GetPosition());
        mat.SetRotationRadiansRH(GetRotation().x, GetRotation().y, GetRotation().z);
        if (m_relativeScale != CVector3(1.0f, 1.0f, 1.0f))
        {
            CMatrix4 smat;
            smat.SetScale(m_relativeScale);
            mat = mat * smat;
        }
        m_RelativeTransform = mat;
        m_bUpdateRelative = false;
    }
}

void CSceneNode::SetRelativeTransform(const CMatrix4 &mat4)
{
    m_RelativeTransform = mat4;
    m_bNeedUpdate = true;
    m_bUpdateRelative = false;
}

} // namespace magic
