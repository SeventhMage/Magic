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

    virtual IShaderProgram *GetShaderProgram() const = 0;
    virtual int GetRenderQueue() const = 0;
    virtual ITexture *GetTexture(int slot) const = 0;
    virtual int GetTextureCount() const = 0;
    virtual IBufferObject *GetVertexArrayObject() const = 0;
    virtual IBufferObject *GetVertexBufferObject() const = 0;
    virtual IBufferObject *GetIndexBufferObject() const = 0;
    virtual bool IsTransparent() const = 0;
    virtual void SetRenderQueue(int id) = 0;
    virtual void SetVertexAttribute(int index, int stride, int offset) = 0;
    virtual void SetVertexBuffer(void *vertexes, int size, int first, int count, int mode, int usage) = 0;
    virtual void SetIndexBuffer(void *indices, int idsCount, int idsType, int mode, int usage) = 0;
    virtual void SetShaderProgram(IShaderProgram *pShaderProgram) = 0;
    virtual void SetTexture(int slot, ITexture *texture) = 0;
    virtual void SetTransparent(bool transparent) = 0;
    
};
}
#endif
