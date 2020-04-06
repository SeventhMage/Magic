#ifndef _MAGIC_C_RENDER_INPUT_H_
#define _MAGIC_C_RENDER_INPUT_H_

#include "render/IRenderInput.h"
#include "render/IShaderProgram.h"

#include <vector>

namespace magic
{
class CRenderInput : public IRenderInput
{
public:
    CRenderInput();
    virtual ~CRenderInput();
    virtual IShaderProgram *GetShaderProgram() const { return m_pShaderProgram; }
    virtual int GetRenderQueue() const { return m_RenderQueueID; }
    virtual ITexture *GetTexture(int slot) const;
    virtual int GetTextureCount() const { return m_TextureArray.size(); }
    virtual int GetVertexSize() const;
    virtual int GetVertexStride() const;
    virtual int GetVertexOffset() const;
    virtual bool IsTransparent() const;
    virtual IBufferObject *GetVertexBufferObject() const;
    virtual IBufferObject *GetIndexBufferObject() const;

    virtual void SetRenderQueue(int id);
    virtual void SetVertexBuffer(void *data, int size);
    virtual void SetIndexBuffer(void *data, int size);
    virtual void SetVertexStride(int stride);
    virtual void SetVertexOffset(int location, int offset);
private:
    std::vector<ITexture *> m_TextureArray;
    IShaderProgram *m_pShaderProgram;
    int m_RenderQueueID;
    IBufferObject *m_pVBO;
    IBufferObject *m_pIBO;
};
}

#endif