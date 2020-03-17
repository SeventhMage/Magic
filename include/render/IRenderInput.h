#ifndef _MAGIC_RENDER_IRENDERINPUT_H_
#define _MAGIC_RENDER_IRENDERINPUT_H_

#include "IShaderProgram.h"
#include "ITexture.h"
#include "IBuffer.h"

namespace magic
{
class IRenderInput
{
public:
    virtual ~IRenderInput(){}

    virtual IShaderProgram *GetShaderProgram() = 0;    
    virtual ITexture *GetTexture() = 0;
    virtual IBuffer *GetBuffer() = 0;
    virtual int GetVertexSize() = 0;
    virtual int GetVertexStride() = 0;
    virtual int GetVertexOffset() = 0;
};
}
#endif