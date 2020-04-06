#ifndef _MAGIC_C_RENDERPASS_H_
#define _MAGIC_C_RENDERPASS_H_

#include "render/IRenderPass.h"

namespace magic
{
class CRenderPass : public IRenderPass
{
public:
    CRenderPass(IRenderTarget *pRenderTarget = nullptr);
    virtual ~CRenderPass();
    virtual IRenderTarget *BindRenderTarget();
    virtual void SetRenderTarget(IRenderTarget *);
    virtual IRenderTarget *GetRenderTarget() { return m_pRenderTarget; }
    virtual bool IsEnable();
private:
    IRenderTarget *m_pRenderTarget;
    bool m_bEnable;
};
} // namespace magic

#endif
