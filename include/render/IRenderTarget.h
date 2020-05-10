#ifndef _MAGIC_RENDER_RENDERTARGET_H_
#define _MAGIC_RENDER_RENDERTARGET_H_

#include "base/magicType.h"
#include "render/ITexture.h"

namespace magic
{
class IRenderTarget
{
public:
    virtual ~IRenderTarget(){}
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual void BeginTarget() = 0;
	virtual void EndTarget() = 0;
	virtual ITexture *GetBindTexture(int index) const = 0;
    virtual uint GetBindTextureCount() const = 0;
	virtual ITexture *GetDepthTexture() const = 0;

};
}

#endif
