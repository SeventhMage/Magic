#include "CGLES3IndexBufferObject.h"
#include "GLESDebug.h"

namespace magic
{
CGLES3IndexBufferObject::CGLES3IndexBufferObject(void *indices, GLsizei idsCount, GLenum idsType, GLenum mode, GLenum usage)
    : m_gpuBufferMode(mode), m_gpuBufferUsage(usage), m_uIndicesNum(idsCount), m_idsType(idsType)
{
    GLDebug(glGenBuffers(1, &m_IBO));
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
    GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetGLVariableSize(idsType) * idsCount, indices, usage));
}

CGLES3IndexBufferObject::~CGLES3IndexBufferObject()
{
    GLDebug(glDeleteBuffers(1, &m_IBO));
}

void CGLES3IndexBufferObject::BufferData(void *indices, int idsSize)
{
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
    GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, idsSize, indices, m_gpuBufferUsage));
}

void CGLES3IndexBufferObject::BufferSubData(void *data, int size, int offset)
{
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
    GLDebug(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
}

void CGLES3IndexBufferObject::Bind()
{
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
}

void CGLES3IndexBufferObject::UnBind()
{
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
} // namespace magic