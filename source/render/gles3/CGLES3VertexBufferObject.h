#ifndef _MAGIC_CGLES3VERTEXBUFFEROBJECT_H_
#define _MAGIC_CGLES3VERTEXBUFFEROBJECT_H_

#include "render/IBufferObject.h"
#include "gl3.h"

namespace magic
{
class CGLES3VertexBufferObject : public IBufferObject
{
public:
    CGLES3VertexBufferObject(void *vertexes, int size, int first, int count, GLenum mode, GLenum usage);
    virtual ~CGLES3VertexBufferObject();

    virtual void Bind();
    virtual void UnBind();

    virtual void BufferData(void *data, int size);
    virtual void BufferSubData(void *data, int size, int offset);

    virtual int GetMode() const { return m_mode; }
    virtual int GetVerticesCount() const { return m_count; }
    virtual int GetFirstIndex() const { return m_first; }

private:
    GLuint m_hVBO;
    int m_vertSize;
    int m_first;
    int m_count;
    GLenum m_mode;
    GLenum m_usage;
};
} // namespace magic

#endif