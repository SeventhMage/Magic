#include "component/CCameraComponent.h"

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
}

void CCameraComponent::Initialize(IRenderer *pRenderer, CameraType type)
{
    m_pRenderPass = pRenderer->CreateRenderPass();
    m_Type = type;
}

void CCameraComponent::Update()
{
   
}

}
