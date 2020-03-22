#ifndef _MAGIC_RENDER_IRENDERINPUT_H_
#define _MAGIC_RENDER_IRENDERINPUT_H_

#include "ITexture.h"
#include "IBuffer.h"
#include "SShaderParam.h"

namespace magic
{
class IRenderInput
{
public:
    virtual ~IRenderInput(){}

    virtual const SShaderParam &GetShaderParam() = 0;
    virtual int GetMaterialID() = 0;
    virtual ITexture *GetTexture() = 0;
    virtual IBuffer *GetBuffer() = 0;
    virtual int GetVertexSize() = 0;
    virtual int GetVertexStride() = 0;
    virtual int GetVertexOffset() = 0;
};
}
#endif