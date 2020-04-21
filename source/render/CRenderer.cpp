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

CRenderer::~CRenderer()
{
    for (size_t i = 0; i < m_RenderPassVec.size(); ++i)
    {
        SAFE_DEL(m_RenderPassVec[i]);
    }
    m_RenderPassVec.clear();
}

void CRenderer::Render(IRenderInput *pRenderInput, IRenderPass *pRenderPass)
{

    //call platform api to real draw
}

IRenderPass *CRenderer::GenerateRenderPass()
{
    IRenderPass *pRenderPass = new CRenderPass(this, nullptr);
    m_RenderPassVec.push_back(pRenderPass);
    return pRenderPass;
}
IRenderTarget *CRenderer::CreateRenderTarget(int width, int height, int format)
{
    return nullptr;
}

IRenderInput *CRenderer::CreateRenderInput(int mode, int usage)
{
    return new CRenderInput(this, mode, usage);
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
                    Render(input, pass);
                }
            }
            for (auto queIt : m_TransparentRenderQueueGroup)
            {
                for (auto input : queIt.second)
                {
                    Render(input, pass);
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
