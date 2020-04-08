#include "CGLES3VertexBufferObject.h"
#include "GLESDebug.h"

namespace magic
{
CGLES3VertexBufferObject::CLGES3VertexBufferObject(void *vertexes, int size, int first, int count, GLenum mode, GLenum usage)
    : m_mode(mode), m_vertSize(size), m_first(first), m_count(count), m_usage(usage)
{
    GLDebug(glGenBuffers(1, &m_hVBO));
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
    GLDebug(glBufferData(GL_ARRAY_BUFFER, size, vertexes, m_usage));
}

CLGES3VertexBufferObject::~CLGES3VertexBufferObject()
{
    GLDebug(glDeleteBuffers(1, &m_hVBO));
}

void CLGES3VertexBufferObject::BufferData(void *data, int size)
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
    GLDebug(glBufferData(GL_ARRAY_BUFFER, size, data, m_usage));
}

void CLGES3VertexBufferObject::BufferSubData(void *data, int size, int offset)
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
    GLDebug(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void CLGES3VertexBufferObject::Bind()
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
}

void CLGES3VertexBufferObject::UnBind()
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
} // namespace magic