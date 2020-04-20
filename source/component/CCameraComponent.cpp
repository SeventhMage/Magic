#include "component/CCameraComponent.h"
#include "base/magicDef.h"
#include "ISceneNode.h"
#include "IGameObject.h"

#include <string.h>

namespace magic
{
CCameraComponent::CCameraComponent()
:m_pRenderPass(nullptr)
,m_Type(CameraType::Projection)
,m_Width(1)
,m_Height(1)
,m_NearClip(1)
,m_FarClip(1000.f)
,m_Fov(1.046f)
,m_Aspect(1.f)
{
    
}

CCameraComponent::~CCameraComponent()
{
    SAFE_DEL(m_pRenderPass);
}

void CCameraComponent::Initialize(IRenderer *pRenderer, CameraType type, float fov, float aspect, float near, float far)
{
    m_pRenderPass = pRenderer->GenerateRenderPass();
    m_Type = type;
    if (m_Type == CameraType::Projection)
    {
        m_Fov = fov;
        m_Aspect = aspect;
    }
    else
    {
        m_Width = fov;
        m_Height = aspect;
    }
    m_NearClip = near;
    m_FarClip = far;
}

void CCameraComponent::SetClearBit(int bit)
{
    m_pRenderPass->SetClearBit(bit);
}

void CCameraComponent::SetClearColor(float r, float g, float b, float a)
{
    m_pRenderPass->SetClearColor(r, g, b, a);
}

void CCameraComponent::Update()
{
    ISceneNode *pNode = m_pGameObject->GetSceneNode();
    m_pRenderPass->SetViewProjectMatirx(m_vpMatrix.m);
}

void CCameraComponent::OnTransformChanged(const CMatrix4 &wordMat)
{
    if (m_Type == CameraType::Ortho)
    {
        m_viewMatrix.BuildProjectionMatrixOrthoRH(m_Width, m_Height, m_NearClip, m_FarClip);
    }
}

}
