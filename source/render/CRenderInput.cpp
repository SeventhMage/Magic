#include "render/CRenderInput.h"

namespace magic
{
CRenderInput::CRenderInput()
:m_pShaderProgram(nullptr)
,m_RenderQueueID(0)
,m_pVAO(nullptr)
,m_pVBO(nullptr)
,m_pIBO(nullptr)
{

}

CRenderInput::~CRenderInput()
{

}

IBufferObject *CRenderInput::GetVertexArrayObject() const
{
    return nullptr;
}

IBufferObject *CRenderInput::GetVertexBufferObject() const
{
    return nullptr;
}

IBufferObject *CRenderInput::GetIndexBufferObject() const
{
    return nullptr;
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

}

void CRenderInput::SetVertexBuffer(void *data, int size)
{

}

void CRenderInput::SetIndexBuffer(void *data, int size)
{

}

void CRenderInput::SetTexture(int slot, ITexture *pTexture)
{

}

}