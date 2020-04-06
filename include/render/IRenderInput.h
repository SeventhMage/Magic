#ifndef _MAGIC_RENDER_IRENDERINPUT_H_
#define _MAGIC_RENDER_IRENDERINPUT_H_

#include "ITexture.h"
#include "IBufferObject.h"
#include "SShaderParam.h"
#include "IShaderProgram.h"

namespace magic
{
class IRenderInput
{
public:
    virtual ~IRenderInput(){}

    virtual void InitializeVertexAttribute(int index, int size, int stride, int offset);
    virtual IShaderProgram *GetShaderProgram() const = 0;
    virtual int GetRenderQueue() const = 0;
    virtual ITexture *GetTexture(int slot) const = 0;
    virtual int GetTextureCount() const = 0;
    virtual bool IsTransparent() const = 0;
    virtual IBufferObject *GetVertexBufferObject() const = 0;
    virtual IBufferObject *GetIndexBufferObject() const = 0;

    virtual void SetRenderQueue(int id) = 0;
    virtual void SetVertexBuffer(void *data, int size) = 0;
    virtual void SetIndexBuffer(void *data, int size) = 0;
    
};
}
#endif