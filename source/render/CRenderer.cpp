#include "CRenderer.h"
#include "CRenderPass.h"
#include "render/CRenderInput.h"

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

IRenderPass *CRenderer::CreateRenderPass()
{
    return new CRenderPass(this, nullptr);
}
IRenderTarget *CRenderer::CreateRenderTarget(int width, int height, int format)
{
    return nullptr;
}

IRenderInput *CRenderer::CreateRenderInput()
{
    return new CRenderInput(this);
}

void CRenderer::Render()
{
    for (auto pass : m_RenderPassVec)
    {
        if (pass->IsEnable())
        {
            pass->BeginRenderTarget();

            for (auto queIt : m_OpaqueRenderQueueGroup)
            {
                for (auto input : queIt.second)
                {
                    Render(input);
                }
            }
            for (auto queIt : m_TransparentRenderQueueGroup)
            {
                for (auto input : queIt.second)
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
