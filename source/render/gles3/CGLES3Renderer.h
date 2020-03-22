#ifndef _MAGIC_C_GLES3RENDERER_H_
#define _MAGIC_C_GLES3RENDERER_H_

#include "../CRenderer.h"

namespace magic
{
class CGLES3Renderer : public CRenderer
{
public:
    virtual void SubmitToRenderQueue(IRenderInput *pInput, int materialId);
    virtual void Render(IRenderInput *pRenderInput, IRenderTarget *pRenderTarget);
    virtual void Render();
};
} // namespace magic

#endif