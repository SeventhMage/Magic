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

void CRenderPass::SetViewProjectMatirx(float *matrix)
{
    memcpy(m_vpMatrix, matrix, sizeof(m_vpMatrix));
}

}
