#ifndef _MAGIC_CGLES3VERTEXBUFFEROBJECT_H_
#define _MAGIC_CGLES3VERTEXBUFFEROBJECT_H_

#include "../CVertexBufferObject.h"
#include "gl3.h"

namespace magic
{
class CGLES3VertexBufferObject : public CVertexBufferObject
{
public:
    CGLES3VertexBufferObject(void *vertexes, int size, int usage, int first, int count, int mode);
    virtual ~CGLES3VertexBufferObject();

    virtual void Bind();
    virtual void UnBind();

    virtual void BufferData(void *data, int size);
    virtual void BufferSubData(void *data, int size, int offset);

private:
    GLuint m_hVBO;
    int m_vertSize;
    GLenum m_usage;
};
} // namespace magic

#endif
