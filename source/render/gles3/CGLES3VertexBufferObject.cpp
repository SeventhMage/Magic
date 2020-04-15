#include "CGLES3VertexBufferObject.h"
#include "GLESDebug.h"

namespace magic
{
CGLES3VertexBufferObject::CGLES3VertexBufferObject(void *vertexes, int size, int usage, int first, int count, int mode)
    :CVertexBufferObject(first, count, mode), m_vertSize(size), m_usage(usage)
{
    GLDebug(glGenBuffers(1, &m_hVBO));
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
    GLDebug(glBufferData(GL_ARRAY_BUFFER, size, vertexes, m_usage));
}

CGLES3VertexBufferObject::~CGLES3VertexBufferObject()
{
    GLDebug(glDeleteBuffers(1, &m_hVBO));
}

void CGLES3VertexBufferObject::BufferData(void *data, int size)
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
    GLDebug(glBufferData(GL_ARRAY_BUFFER, size, data, m_usage));
}

void CGLES3VertexBufferObject::BufferSubData(void *data, int size, int offset)
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
    GLDebug(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void CGLES3VertexBufferObject::Bind()
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
}

void CGLES3VertexBufferObject::UnBind()
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
} // namespace magic
