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
    virtual void BeginRenderTarget() = 0;
    virtual IRenderTarget *GetRenderTarget() = 0;
    virtual bool IsEnable() const = 0;
    
    virtual void SetRenderTarget(IRenderTarget *) = 0;
    virtual void SetClearColor(float a, float r, float g, float b) = 0;
    virtual void SetClearBit(int bit) = 0;
    virtual void SetEnable(bool) = 0;
};
} // namespace magic

#endif
