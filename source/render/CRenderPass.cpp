#include "CRenderPass.h"

#include <string.h>
#include <algorithm>

namespace magic
{
CRenderPass::CRenderPass(IRenderer *pRenderer, IRenderTarget *pRenderTarget)
:m_pRenderer(pRenderer)
,m_pRenderTarget(pRenderTarget)
,m_ClearBit(0)
,m_RenderFlag(0)
,m_bEnable(true)
{
    memset(m_ClearColor, 0, sizeof(m_ClearColor));
}

CRenderPass::~CRenderPass()
{
    for (auto &param : m_ShaderParams)
    {
        delete param;
    }
}

void CRenderPass::BeginRenderTarget()
{
    if (m_pRenderTarget)
    {
        m_pRenderTarget->BeginTarget();
        m_pRenderer->Viewport(0, 0, m_pRenderTarget->GetWidth(), m_pRenderTarget->GetHeight());
    }
    else
    {
        m_pRenderer->Viewport(0, 0, m_pRenderer->GetWindowWidth(), m_pRenderer->GetWindowHeight());
    }
    
    m_pRenderer->SetClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    m_pRenderer->Clear(m_ClearBit);
}

void CRenderPass::EndRenderTarget()
{
    if (m_pRenderTarget)
        m_pRenderTarget->EndTarget();
}

void CRenderPass::SetClearColor(float r, float g, float b, float a)
{
    m_ClearColor[0] = r;
    m_ClearColor[1] = g;
    m_ClearColor[2] = b;
    m_ClearColor[3] = a;
}

void CRenderPass::SetShaderParam(const char *name, void *value, int size)
{
    auto it = std::find_if(m_ShaderParams.begin(), m_ShaderParams.end(), [=](SShaderParam* param){return !strcmp(param->paramName, name);});
    if (it == m_ShaderParams.end())
    {
        SShaderParam *param = new SShaderParam(name, value, size);
        m_ShaderParams.push_back(param);
        
    }
    else
    {
        (*it)->SetValue(value, size);
    }
}

SShaderParam *CRenderPass::GetShaderParam(int index) const
{
    if (index >=0 && index < m_ShaderParams.size())
    {
        return m_ShaderParams[index];
    }
    return nullptr;
}

}
