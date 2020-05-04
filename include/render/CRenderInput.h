#ifndef _MAGIC_C_RENDER_INPUT_H_
#define _MAGIC_C_RENDER_INPUT_H_

#include "render/IRenderInput.h"
#include "render/IShaderProgram.h"
#include "render/IRenderer.h"

#include <vector>

namespace magic
{
class CRenderInput : public IRenderInput
{
public:
    static const int MAX_TEXTURE_NUM = 32;
    CRenderInput(IRenderer *pRenderer, int mode, int usage);
    virtual ~CRenderInput();
    virtual IShaderProgram *GetShaderProgram() const { return m_pShaderProgram; }
    virtual int GetRenderQueue() const { return m_RenderQueueID; }
    virtual ITexture *GetTexture(int slot) const;
    virtual int GetTextureCount() const { return m_TextureCount; }
    virtual IBufferObject *GetVertexArrayObject() const;
    virtual IBufferObject *GetVertexBufferObject() const;
    virtual IBufferObject *GetIndexBufferObject() const;
    virtual int GetMode() const { return m_Mode; }
    virtual int GetFirst() const { return m_First; }
    virtual int GetIndexType() const { return m_IndexType; }
    virtual int GetVerticesCount() const { return m_VerticesCount; }
    virtual int GetIndicesCount() const { return m_IndicesCount; }
    virtual bool IsTransparent() const { return m_bTransparent; }

    virtual void SetRenderQueue(int id);
    virtual void SetVertexAttribute(int index, int size, int stride, int offset);
    virtual void SetVertexBuffer(void *vertices, int size, int offset);
    virtual void SetIndexBuffer(void *indices, int size, int offset);
    virtual void CreateVertexBufferObject(void *vertices, int size, int usage);
    virtual void CreateIndexBufferObject(void *indices, int size, int usage);
    virtual void SetShaderProgram(IShaderProgram *pShaderProgram);
    virtual void SetTexture(int slot, ITexture *texture);
    virtual void SetTransparent(bool transparent) { m_bTransparent = transparent; }
    virtual void BeginInput(int first, int vertCount, int indicesCount);
    virtual void EndInput();
    virtual void SetRenderFlag(uint flag) { m_RenderFlag = flag; }
    virtual uint GetRenderFlag() { return m_RenderFlag; }
private:
    IRenderer *m_pRenderer;
    ITexture *m_TextureArray[MAX_TEXTURE_NUM];
    int m_TextureCount;
    IShaderProgram *m_pShaderProgram;
    int m_RenderQueueID;
    IBufferObject *m_pVAO;
    IBufferObject *m_pVBO;
    IBufferObject *m_pIBO;
    int m_Mode;
    int m_Usage;
    int m_First;
    int m_VerticesCount;
    int m_IndicesCount;
    int m_IndexType;
    uint m_RenderFlag;
    bool m_bTransparent;
};
}

#endif
