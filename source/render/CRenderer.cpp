#include "CRenderer.h"

namespace magic
{
CRenderer::CRenderer()
{
}

void CRenderer::Render(IRenderInput *pRenderInput, IRenderTarget *pRenderTarget)
{
    const SShaderParam &shaderParam = pRenderInput->GetShaderParam();
    ITexture *pTexture = pRenderInput->GetTexture();
    IBuffer *pBuffer = pRenderInput->GetBuffer();

    //call platform api to real draw
}

void CRenderer::CreateRenderPass(const CMatrix4 &viewProjMatrix)
{
    
}

void CRenderer::Render()
{
    for (auto pass : m_RenderPassVec)
    {
        if (pass->IsEnable())
        {
            IRenderTarget *pRenderTarget = pass->BindRenderTarget();
            for (auto queIt: m_RenderQueueGroup)
            {
                for (auto input: queIt.second)
                {
                    Render(input, pRenderTarget);
                }
            }
        }
    }
    m_RenderQueueGroup.clear();
}

void CRenderer::SubmitToRenderQueue(IRenderInput *pInput, int materialId)
{
    m_RenderQueueGroup[materialId].push_back(pInput);
}


} // namespace magic