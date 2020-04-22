#include "CRenderPass.h"

#include <string.h>

namespace magic
{
CRenderPass::CRenderPass(IRenderer *pRenderer, IRenderTarget *pRenderTarget)
:m_pRenderer(pRenderer)
,m_pRenderTarget(pRenderTarget)
,m_ClearBit(0)
,m_bEnable(true)
{
    memset(m_ClearColor, 0, sizeof(m_ClearColor));
}

CRenderPass::~CRenderPass()
{
    for (auto it : m_ShaderParams)
    {
        delete it.second;
    }
}

void CRenderPass::BeginRenderTarget()
{
    if (m_pRenderTarget)
        m_pRenderTarget->BeginTarget();
    m_pRenderer->SetClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    m_pRenderer->Clear(m_ClearBit);
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
    auto it = m_ShaderParams.find(name);
    if (it == m_ShaderParams.end())
    {
        SShaderParam *param = new SShaderParam(name, value, size);
        m_ShaderParams[name] = param;
    }
    else
    {
        m_ShaderParams[name]->SetValue(value, size);
    }
}

SShaderParam *CRenderPass::GetShaderParam(int index) const
{
    if (index >=0 && index < m_ShaderParams.size())
    {
        auto it = m_ShaderParams.begin();
        for (int i=0; i<index; ++it);
        return it->second;
    }
    return nullptr;
}

}
