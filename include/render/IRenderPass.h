#ifndef _MAGIC_I_RENDER_PASS_H_
#define _MAGIC_I_RENDER_PASS_H_

#include "IRenderTarget.h"
#include "SShaderParam.h"

namespace magic
{
class IRenderPass
{
public:
    virtual ~IRenderPass() {}
    /**
     * bind current render target to render
     * **/
    virtual void BeginRenderTarget() = 0;
    virtual void EndRenderTarget() = 0;
    virtual IRenderTarget *GetRenderTarget() = 0;
    virtual bool IsEnable() const = 0;
    virtual SShaderParam *GetShaderParam(int index) const = 0;
    virtual int GetShaderParamCount() const = 0;
    
    virtual void SetRenderTarget(IRenderTarget *) = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;
    virtual void SetClearBit(int bit) = 0;
    virtual void SetShaderParam(const char *name, void *value, int size) = 0;
    virtual void SetEnable(bool) = 0;
    virtual void SetRenderFlag(uint flag) = 0;
    virtual uint GetRenderFlag() = 0;
};
} // namespace magic

#endif
