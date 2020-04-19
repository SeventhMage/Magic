#ifndef _MAGIC_C_GLES3INDEXBUFFEROBJECT_H_
#define _MAGIC_C_GLES3INDEXBUFFEROBJECT_H_

#include "../CIndexBufferObject.h"
#include "gl3.h"

namespace magic
{
class CGLES3IndexBufferObject : public CIndexBufferObject
{
public:
    CGLES3IndexBufferObject(void *indices, int size, int usage);
    virtual ~CGLES3IndexBufferObject();

    virtual void Bind();
    virtual void UnBind();

    virtual void BufferData(void *indices, int idsSize);
    virtual void BufferSubData(void *data, int size, int offset);
private:
    GLuint m_IBO;
    GLenum m_gpuBufferUsage;
};
} // namespace magic

#endif
