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
{
    
}

CCameraComponent::~CCameraComponent()
{
    SAFE_DEL(m_pRenderPass);
}

void CCameraComponent::Initialize(IRenderer *pRenderer, CameraType type)
{
    m_pRenderPass = pRenderer->GenerateRenderPass();
    m_Type = type;
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

}
