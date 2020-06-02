#include "component/CCameraComponent.h"
#include "base/magicDef.h"
#include "scene/ISceneNode.h"
#include "scene/IGameObject.h"

#include <string.h>

namespace magic
{
uint CCameraComponent::s_FlagCount = 1;
CCameraComponent::CCameraComponent()
:m_pRenderPass(nullptr)
,m_pRenderer(nullptr)
,m_Type(CameraType::Projection)
,m_Width(1)
,m_Height(1)
,m_NearClip(1)
,m_FarClip(1000.f)
,m_Fov(1.046f)
,m_Aspect(1.f)
,m_bNeedUpdateView(true)
,m_bNeedUpdateProj(true)
,m_Flag(s_FlagCount)
{
    s_FlagCount <<= 1;
}

CCameraComponent::~CCameraComponent()
{
    m_pRenderer->DestroyRenderPass(m_pRenderPass);
}

void CCameraComponent::Initialize(IRenderer *pRenderer, CameraType type, float fov, float aspect, float near, float far)
{
    m_pRenderPass = pRenderer->GenerateRenderPass();
    m_pRenderPass->SetRenderFlag(m_Flag);
    m_pRenderer = pRenderer;
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

	Update();
}

void CCameraComponent::SetClearBit(int bit)
{
    m_pRenderPass->SetClearBit(bit);
}

void CCameraComponent::SetClearColor(float r, float g, float b, float a)
{
    m_pRenderPass->SetClearColor(r, g, b, a);
}

void CCameraComponent::SetRenderTarget(IRenderTarget *target)
{
    m_pRenderPass->SetRenderTarget(target);
}

void CCameraComponent::SetEnable(bool bEnable)
{
    m_pRenderPass->BeginRenderTarget();
    if (m_pRenderPass)
        m_pRenderPass->SetEnable(bEnable);
    m_pRenderPass->EndRenderTarget();
}

bool CCameraComponent::IsEnable()
{
    if (m_pRenderPass)
        return m_pRenderPass->IsEnable();
    return false;
}

void CCameraComponent::Update()
{
    ISceneNode *pSceneNode = m_pGameObject->GetSceneNode();
    if (m_bNeedUpdateView)
    {
        CMatrix4 transform = pSceneNode->GetAbsluateTransform();
        transform.SetTranslation(CVector3(0, 0, 0));
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
        m_pRenderPass->SetShaderParam("viewMatrix", m_viewMatrix.m, sizeof(m_viewMatrix.m));
        m_pRenderPass->SetShaderParam("projMatrix", m_projMatrix.m, sizeof(m_projMatrix.m));
        m_pRenderPass->SetShaderParam("viewProjMatrix", m_vpMatrix.m, sizeof(m_vpMatrix.m));
        m_pRenderPass->SetShaderParam("viewPosition", pSceneNode->GetAbslutePosition().v, sizeof(CVector3));
        m_bNeedUpdateView = false;
        m_bNeedUpdateProj = false;
    }
}

void CCameraComponent::OnTransformChanged(const CMatrix4 &wordMat)
{
    m_bNeedUpdateView = true;
}

}
