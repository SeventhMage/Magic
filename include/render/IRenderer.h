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
    virtual void Render(IRenderInput *pRenderInput, IRenderTarget *pRenderTarget) = 0;
};
} // namespace magic

#endif