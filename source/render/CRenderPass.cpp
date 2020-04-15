#include "CRenderPass.h"

#include <string.h>

namespace magic
{
CRenderPass::CRenderPass(IRenderer *pRenderer, IRenderTarget *pRenderTarget)
:m_pRenderer(pRenderer)
,m_pRenderTarget(pRenderTarget)
,m_ClearBit(0)
,m_bEnable(false)
{
    memset(m_ClearColor, 0, sizeof(m_ClearColor));
}

CRenderPass::~CRenderPass()
{

}

void CRenderPass::BeginRenderTarget()
{
    m_pRenderTarget->BeginTarget();
    m_pRenderer->SetClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    m_pRenderer->Clear(m_ClearBit);
}

void CRenderPass::SetClearColor(float a, float r, float g, float b)
{
    m_ClearColor[0] = a;
    m_ClearColor[1] = r;
    m_ClearColor[2] = g;
    m_ClearColor[3] = b;
}

void CRenderPass::SetViewProjectMatirx(float *matrix)
{
    memcpy(m_vpMatrix, matrix, sizeof(m_vpMatrix));
}

}
