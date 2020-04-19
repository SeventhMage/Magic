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
    virtual ~CRenderer();

    virtual IRenderPass *GenerateRenderPass();
    virtual void SubmitToRenderQueue(IRenderInput *pInput);
    virtual void Render();
    virtual IRenderTarget *CreateRenderTarget(int width, int height, int format);
    virtual IRenderInput *CreateRenderInput(int mode, int usage);
    
protected:
    virtual void Render(IRenderInput *pRenderInput);
private:
    typedef std::map<int, std::vector<IRenderInput*> > RenderQueueGroup;
    RenderQueueGroup m_OpaqueRenderQueueGroup;
    RenderQueueGroup m_TransparentRenderQueueGroup;
    std::vector<IRenderPass *> m_RenderPassVec;
};
}

#endif
