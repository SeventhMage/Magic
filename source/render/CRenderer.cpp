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

void CRenderer::DestroyRenderPass(IRenderPass *pass)
{
    if (pass)
    {
        auto it = std::find(m_RenderPassVec.begin(), m_RenderPassVec.end(), pass);
        if (it != m_RenderPassVec.end())
        {
            m_RenderPassVec.erase(it);
        }
        delete pass;
    }
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
                    if (input->GetRenderFlag() & pass->GetRenderFlag())
                        Render(input, pass);
                }
            }
            for (auto queIt : m_TransparentRenderQueueGroup)
            {
                for (auto input : queIt.second)
                {
                    if (input->GetRenderFlag() & pass->GetRenderFlag())
                        Render(input, pass);
                }
            }
            
            pass->EndRenderTarget();
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
