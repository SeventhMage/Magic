#ifndef _MAGIC_I_RENDER_PASS_H_
#define _MAGIC_I_RENDER_PASS_H_

#include "IRenderTarget.h"

namespace magic
{
class IRenderPass
{
public:
    /**
     * bind current render target to render
     * **/
    virtual IRenderTarget *BindRenderTarget() = 0;
    virtual void SetRenderTarget(IRenderTarget *) = 0;
    virtual IRenderTarget *GetRenderTarget() = 0;
    virtual bool IsEnable() const = 0;
};
} // namespace magic

#endif
