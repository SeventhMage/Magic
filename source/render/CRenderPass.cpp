#include "CRenderPass.h"

namespace magic
{
CRenderPass::CRenderPass(IRenderTarget *pRenderTarget)
:m_pRenderTarget(pRenderTarget)
,m_bEnable(false)
{

}

CRenderPass::~CRenderPass()
{

}

IRenderTarget *CRenderPass::BindRenderTarget()
{
    return m_pRenderTarget;
}

void CRenderPass::SetRenderTarget(IRenderTarget *target)
{
    m_pRenderTarget = target;
}

}
