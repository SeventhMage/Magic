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
    virtual int GetIndicesCount() const = 0;
    virtual IBufferObject *GetVertexArrayObject() const = 0;
    virtual IBufferObject *GetVertexBufferObject() const = 0;
    virtual IBufferObject *GetIndexBufferObject() const = 0;
    virtual int GetMode() const = 0;
    virtual int GetFirst() const = 0;
    virtual int GetIndexType() const = 0;
    virtual int GetVerticesCount() const = 0;
    virtual bool IsTransparent() const = 0;
    virtual void SetRenderQueue(int id) = 0;
    virtual void SetVertexAttribute(int index, int size, int stride, int offset) = 0;
    virtual void SetVertexBuffer(void *vertices, int size, int offset) = 0;
    virtual void SetIndexBuffer(void *indices, int size, int offset) = 0;
    virtual void CreateVertexBufferObject(void *verties, int size, int usage) = 0;
    virtual void CreateIndexBufferObject(void *indices, int size, int usage) = 0;
    virtual void SetShaderProgram(IShaderProgram *pShaderProgram) = 0;
    virtual void SetTexture(int slot, ITexture *texture) = 0;
    virtual void SetTransparent(bool transparent) = 0;
    virtual void BeginInput(int first, int vertCount, int indicesCount) = 0;
    virtual void EndInput() = 0;
    virtual void SetRenderFlag(uint flag) = 0;
    virtual uint GetRenderFlag() = 0;
    
};
}
#endif
