#include "CGLES3IndexBufferObject.h"
#include "GLESDebug.h"
#include "GLESType.h"

namespace magic
{
CGLES3IndexBufferObject::CGLES3IndexBufferObject(void *indices, int size, int usage)
: m_gpuBufferUsage(usage)
{
    GLDebug(glGenBuffers(1, &m_IBO));
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
    GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GetGLGPUBufferUsage((GPUBufferUsage)usage)));
}

CGLES3IndexBufferObject::~CGLES3IndexBufferObject()
{
    GLDebug(glDeleteBuffers(1, &m_IBO));
}

void CGLES3IndexBufferObject::BufferData(void *indices, int idsSize)
{
    GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
    GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, idsSize, indices, GetGLGPUBufferUsage((GPUBufferUsage)m_gpuBufferUsage)));
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
