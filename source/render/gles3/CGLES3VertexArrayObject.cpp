#include "CGLES3VertexArrayObject.h"
#include "GLESDebug.h"

namespace magic
{
CGLES3VertexArrayObject::CGLES3VertexArrayObject()
{
    GLDebug(glGenVertexArrays(1, &m_hVAO));
}

CGLES3VertexArrayObject::~CGLES3VertexArrayObject()
{
    GLDebug(glDeleteVertexArrays(1, &m_hVAO));
}

void CGLES3VertexArrayObject::Bind()
{
    GLDebug(glBindVertexArray(m_hVAO));
}

void CGLES3VertexArrayObject::UnBind()
{
    GLDebug(glBindVertexArray(0));
}

void CGLES3VertexArrayObject::EnableVertexAttrib(int vertexArrayIndex, int size, int vertType, int stride, int offset)
{
    GLDebug(glEnableVertexAttribArray(vertexArrayIndex));
    GLDebug(glVertexAttribPointer(vertexArrayIndex, size, vertType, false, stride, (GLvoid *)offset));
}
}