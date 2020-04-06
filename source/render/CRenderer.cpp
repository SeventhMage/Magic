#include "CRenderer.h"
#include "CRenderInput.h"

namespace magic
{
CRenderer::CRenderer()
{
    //Init Renderer
    //Set clear color
}

void CRenderer::Render(IRenderInput *pRenderInput)
{

    //call platform api to real draw
}

void CRenderer::CreateRenderPass(const CMatrix4 &viewProjMatrix)
{
    
}
IRenderTarget *CRenderer::CreateRenderTarget(int width, int height, int format)
{
    return nullptr;
}

IRenderInput *CRenderer::CreateRenderInput()
{
    return new CRenderInput();
}

void CRenderer::Render()
{
    for (auto pass : m_RenderPassVec)
    {
        if (pass->IsEnable())
        {
            IRenderTarget *pRenderTarget = pass->BindRenderTarget();
            for (auto queIt: m_OpaqueRenderQueueGroup)
            {
                for (auto input: queIt.second)
                {
                    Render(input);
                }
            }

            for (auto queIt: m_TransparentRenderQueueGroup)
            {
                for (auto input: queIt.second)
                {
                    Render(input);
                }
            }
        }
    }
    m_OpaqueRenderQueueGroup.clear();
    m_TransparentRenderQueueGroup.clear();
}

void CRenderer::SubmitToRenderQueue(IRenderInput *pInput)
{
    int renderqueue = pInput->GetRenderQueue();
    if (pInput->IsTransparent())
        m_TransparentRenderQueueGroup[renderqueue].push_back(pInput);
    else
        m_OpaqueRenderQueueGroup[renderqueue].push_back(pInput);
}


} // namespace magic