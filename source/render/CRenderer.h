#ifndef _MAGIC_RENDER_CRENDERER_H_
#define _MAGIC_RENDER_CRENDERER_H_

#include "render/IRenderer.h"
#include "render/IRenderPass.h"

#include <vector>
#include <map>

namespace magic
{
class CRenderer : public IRenderer
{
public:
    CRenderer();

    virtual void CreateRenderPass(const CMatrix4 &viewProjMatrix);
    virtual void SubmitToRenderQueue(IRenderInput *pInput, int materialId);
    virtual void Render(IRenderInput *pRenderInput, IRenderTarget *pRenderTarget);
    virtual void Render();
    virtual IRenderTarget *CreateRenderTarget(int width, int height, int format);
private:
    typedef std::map<int, std::vector<IRenderInput*> > RenderQueueGroup;
    RenderQueueGroup m_RenderQueueGroup;
    std::vector<IRenderPass *> m_RenderPassVec;
};
}

#endif