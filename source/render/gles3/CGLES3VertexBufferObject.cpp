#include "CGLES3VertexBufferObject.h"
#include "GLESDebug.h"
#include "GLESType.h"

namespace magic
{
CGLES3VertexBufferObject::CGLES3VertexBufferObject(void *vertices, int size, int usage)
    :m_vertSize(size), m_usage(usage)
{
    GLDebug(glGenBuffers(1, &m_hVBO));
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
    GLDebug(glBufferData(GL_ARRAY_BUFFER, size, vertices, GetGLGPUBufferUsage((GPUBufferUsage)m_usage)));
}

CGLES3VertexBufferObject::~CGLES3VertexBufferObject()
{
    GLDebug(glDeleteBuffers(1, &m_hVBO));
}

void CGLES3VertexBufferObject::BufferData(void *data, int size)
{
    GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
    GLDebug(glBufferData(GL_ARRAY_BUFFER, size, data, GetGLGPUBufferUsage((GPUBufferUsage)m_usage)));
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
