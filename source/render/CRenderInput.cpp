#include "render/CRenderInput.h"
#include "render/ERender.h"
#include "CVertexArrayObject.h"
#include "CVertexBufferObject.h"
#include "CIndexBufferObject.h"

namespace magic
{
CRenderInput::CRenderInput(IRenderer *pRenderer)
:m_pRenderer(pRenderer)
,m_pShaderProgram(nullptr)
,m_RenderQueueID(0)
,m_pVAO(nullptr)
,m_pVBO(nullptr)
,m_pIBO(nullptr)
{
    memset(m_TextureArray, 0, sizeof(ITexture *) * MAX_TEXTURE_NUM);
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
    if (!m_pVAO)
        m_pVAO = m_pRenderer->CreateVertexArrayObject();
    ((CVertexArrayObject *)m_pVAO)->EnableVertexAttrib(index, size, VariableType::FLOAT, stride, offset);
}

void CRenderInput::SetVertexBuffer(void *vertexes, int size, int usage, int first, int count, int mode)
{
    if (!m_pVBO)
        m_pVBO = m_pRenderer->CreateVertexBufferObject(vertexes, size, usage, first, count, mode);
}

void CRenderInput::SetIndexBuffer(void *indices, int idsCount, int idsType, int mode, int usage)
{
    if (!m_pIBO)
        m_pIBO = m_pRenderer->CreateIndexBufferObject(indices, idsCount, idsType, mode, usage);
}

void CRenderInput::SetTexture(int slot, ITexture *pTexture)
{
    if (slot >=0 && slot < MAX_TEXTURE_NUM)
    {
        m_TextureArray[slot] = pTexture;
    }
}

}