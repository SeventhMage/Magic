#ifndef _MAGIC_RENDER_RENDERTARGET_H_
#define _MAGIC_RENDER_RENDERTARGET_H_

#include "base/magicType.h"

namespace magic
{
class IRenderTarget
{
public:
    virtual ~IRenderTarget(){}
    virtual int GetWindow() const = 0;
    virtual int GetHeight() const = 0;
    virtual uint GetHandle() const = 0;
};
}

#endif