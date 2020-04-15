#include "component/CCameraComponent.h"
#include "base/magicDef.h"

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
    m_pRenderPass = pRenderer->CreateRenderPass();
    m_Type = type;
}

void CCameraComponent::Update()
{
   
}

}
