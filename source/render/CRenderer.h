#ifndef _MAGIC_RENDER_CRENDERER_H_
#define _MAGIC_RENDER_CRENDERER_H_

#include "../../include/render/IRenderer.h"

namespace magic
{
class CRenderer : public IRenderer
{
public:
    CRenderer();
    virtual void Render(IRenderInput *pRenderInput, IRenderTarget *pRenderTarget);
};
}

#endif