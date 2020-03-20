#ifndef _MAGIC__RENDER_RENDERER_H_
#define _MAGIC__RENDER_RENDERER_H_

#include "IRenderInput.h"
#include "IRenderTarget.h"

namespace magic
{
class IRenderer
{
public:
    virtual ~IRenderer(){}
    /**
     * Initalize RenderQueue by config.
     **/
    virtual void Initalize() = 0;
    virtual void Render(IRenderInput *pRenderInput, IRenderTarget *pRenderTarget) = 0;
    virtual void SubmitToRenderQueue(IRenderInput *, int queueId) = 0;
};
} // namespace magic

#endif