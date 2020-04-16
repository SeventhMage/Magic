#ifndef _MAGIC_C_RENDER_INPUT_H_
#define _MAGIC_C_RENDER_INPUT_H_

#include "render/IRenderInput.h"
#include "render/IShaderProgram.h"
#include "render/IRenderer.h"
#include "CVertexArrayObject.h"
#include "CVertexBufferObject.h"
#include "CIndexBufferObject.h"

#include <vector>

namespace magic
{
class CRenderInput : public IRenderInput
{
public:
    static const int MAX_TEXTURE_NUM = 32;
    CRenderInput(IRenderer *pRenderer);
    virtual ~CRenderInput();
    virtual IShaderProgram *GetShaderProgram() const { return m_pShaderProgram; }
    virtual int GetRenderQueue() const { return m_RenderQueueID; }
    virtual ITexture *GetTexture(int slot) const;
    virtual int GetTextureCount() const { return m_TextureCount; }
    virtual IBufferObject *GetVertexArrayObject() const;
    virtual IBufferObject *GetVertexBufferObject() const;
    virtual IBufferObject *GetIndexBufferObject() const;
    virtual bool IsTransparent() const { return m_bTransparent; }

    virtual void SetRenderQueue(int id);
    virtual void SetVertexAttribute(int index, int size, int stride, int offset);
    virtual void SetVertexBuffer(void *data, int size);
    virtual void SetIndexBuffer(void *data, int size);
    virtual void SetShaderProgram(IShaderProgram *pShaderProgram);
    virtual void SetTexture(int slot, ITexture *texture);
    virtual void SetTransparent(bool transparent) { m_bTransparent = transparent; }
private:
    IRenderer *m_pRenderer;
    ITexture *m_TextureArray[MAX_TEXTURE_NUM];
    int m_TextureCount;
    IShaderProgram *m_pShaderProgram;
    int m_RenderQueueID;
    CVertexArrayObject *m_pVAO;
    CVertexBufferObject *m_pVBO;
    CIndexBufferObject *m_pIBO;
    bool m_bTransparent;
};
}

#endif
