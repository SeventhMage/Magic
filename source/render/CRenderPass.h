#ifndef _MAGIC_C_RENDERPASS_H_
#define _MAGIC_C_RENDERPASS_H_

#include "render/IRenderPass.h"
#include "render/IRenderer.h"
#include "render/SShaderParam.h"

#include <vector>
#include <string>

namespace magic
{
class CRenderPass : public IRenderPass
{
public:
    CRenderPass(IRenderer *pRenderer, IRenderTarget *pRenderTarget = nullptr);
    virtual ~CRenderPass();
    virtual void BeginRenderTarget();
    virtual void EndRenderTarget();
    virtual void SetRenderTarget(IRenderTarget *pRenderTarget) { m_pRenderTarget = pRenderTarget; }
    virtual IRenderTarget *GetRenderTarget() { return m_pRenderTarget; }
    virtual SShaderParam *GetShaderParam(int index) const;
    virtual int GetShaderParamCount() const { return (int)m_ShaderParams.size(); }
    virtual bool IsEnable() const { return m_bEnable; }
    
    virtual void SetClearColor(float r, float g, float b, float a);
    virtual void SetClearBit(int bit) { m_ClearBit = bit; }
    virtual void SetShaderParam(const char *name, void *value, int size);
    virtual void SetEnable(bool enable) { m_bEnable = enable; }
    virtual void SetRenderFlag(uint flag) { m_RenderFlag = flag; }
    virtual uint GetRenderFlag() { return m_RenderFlag; }
private:
    IRenderer *m_pRenderer;
    IRenderTarget *m_pRenderTarget;
    int m_ClearBit;
    float m_ClearColor[4];
    std::vector<SShaderParam *> m_ShaderParams;
    uint m_RenderFlag;
    bool m_bEnable;
};
} // namespace magic

#endif
