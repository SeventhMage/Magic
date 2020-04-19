#include "render/CRenderInput.h"
#include "render/ERender.h"
#include "CVertexArrayObject.h"
#include "CVertexBufferObject.h"
#include "CIndexBufferObject.h"

namespace magic
{
CRenderInput::CRenderInput(IRenderer *pRenderer, int mode, int usage)
:m_pRenderer(pRenderer)
,m_TextureCount(0)
,m_pShaderProgram(nullptr)
,m_RenderQueueID(0)
,m_pVAO(nullptr)
,m_pVBO(nullptr)
,m_pIBO(nullptr)
,m_Mode(mode)
,m_Usage(usage)
,m_First(0)
,m_VerticesCount(0)
,m_IndexType(VariableType::USHORT)
,m_bTransparent(false)
{
    memset(m_TextureArray, 0, sizeof(ITexture *) * MAX_TEXTURE_NUM);
    m_pVAO = m_pRenderer->CreateVertexArrayObject();
}

CRenderInput::~CRenderInput()
{
    SAFE_DEL(m_pVAO);
    SAFE_DEL(m_pVBO);
    SAFE_DEL(m_pIBO);
}

ITexture *CRenderInput::GetTexture(int slot) const
{
    if (slot >=0 && slot < MAX_TEXTURE_NUM)
    {
        return m_TextureArray[slot];
    }
    return nullptr;
}

IBufferObject *CRenderInput::GetVertexArrayObject() const
{
    return m_pVAO;
}

IBufferObject *CRenderInput::GetVertexBufferObject() const
{
    return m_pVBO;
}

IBufferObject *CRenderInput::GetIndexBufferObject() const
{
    return m_pIBO;
}

void CRenderInput::SetRenderQueue(int id)
{
    m_RenderQueueID = id;
}

void CRenderInput::SetShaderProgram(IShaderProgram *pShaderProgram)
{
    m_pShaderProgram = pShaderProgram;
}

void CRenderInput::SetVertexAttribute(int index, int size, int stride, int offset)
{
    ((CVertexArrayObject *)m_pVAO)->EnableVertexAttrib(index, size, VariableType::FLOAT, stride, offset);
}

void CRenderInput::SetVertexBuffer(void *vertices, int size, int offset)
{
    ((CVertexBufferObject *)m_pVBO)->BufferSubData(vertices, size, offset);
}

void CRenderInput::SetIndexBuffer(void *indices, int size, int offset)
{
    ((CIndexBufferObject *)m_pIBO)->BufferSubData(indices, size, offset);
}

void CRenderInput::CreateVertexBufferObject(void *vertices, int size, int usage)
{
    SAFE_DEL(m_pVBO);
    m_pVBO = m_pRenderer->CreateVertexBufferObject(vertices, size, usage);
}

void CRenderInput::CreateIndexBufferObject(void *indices, int size, int usage)
{
    SAFE_DEL(m_pIBO);
    m_pIBO = m_pRenderer->CreateIndexBufferObject(indices, size, usage);
}

void CRenderInput::SetTexture(int slot, ITexture *pTexture)
{
    if (slot >=0 && slot < MAX_TEXTURE_NUM)
    {
        m_TextureArray[slot] = pTexture;
    }
}

void CRenderInput::BeginInput(int first, int vertCount)
{
    m_First = first;
    m_VerticesCount = vertCount;
    m_pVAO->Bind();
}

void CRenderInput::EndInput()
{
    m_pVBO->UnBind();
    if (m_pIBO)
        m_pIBO->UnBind();
    m_pVAO->UnBind();
}

}
