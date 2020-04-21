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
,m_bNeedUpdateView(true)
,m_bNeedUpdateProj(true)
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
    m_bNeedUpdateView = true;
    m_bNeedUpdateProj = true;
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
    if (m_bNeedUpdateView)
    {
        ISceneNode *pSceneNode = m_pGameObject->GetSceneNode();
        const CMatrix4 &transform = pSceneNode->GetAbsluateTransform();
        CVector3 dir(0, 0, -1.f);
        CVector3 up(0, 1.f, 0);
        transform.TransformVect(dir);
        dir.normalize();
        transform.TransformVect(up);
        up.normalize();
        m_viewMatrix.BuildCameraLookAtMatrix(pSceneNode->GetAbslutePosition(), dir, up);
    }
    if (m_bNeedUpdateProj)
    {
        if (m_Type == CameraType::Ortho)
            m_projMatrix.BuildProjectionMatrixOrthoRH(m_Width, m_Height, m_NearClip, m_FarClip);
        else
            m_projMatrix.BuildProjectionMatrixPerspectiveFovRH(m_Fov, m_Aspect, m_NearClip, m_FarClip);
    }
    
    if (m_bNeedUpdateView || m_bNeedUpdateProj)
    {
        m_vpMatrix = m_viewMatrix * m_projMatrix;
        m_pRenderPass->SetShaderParam("vpMatrix", m_vpMatrix.m, sizeof(m_vpMatrix.m));
        m_bNeedUpdateView = false;
        m_bNeedUpdateProj = false;
    }
}

void CCameraComponent::OnTransformChanged(const CMatrix4 &wordMat)
{
    m_bNeedUpdateView = true;
}

}
