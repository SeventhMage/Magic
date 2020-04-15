#ifndef _MAGIC_C_GLES3_VERTEX_ARRAY_OBJECT_H_
#define _MAGIC_C_GLES3_VERTEX_ARRAY_OBJECT_H_

#include "../CVertexArrayObject.h"
#include "gl3.h"

namespace magic
{
class CGLES3VertexArrayObject : public CVertexArrayObject
{
public:
    CGLES3VertexArrayObject();
    virtual ~CGLES3VertexArrayObject();
    virtual void Bind();
    virtual void UnBind();
    virtual void EnableVertexAttrib(int vertexArrayIndex, int size, int vertType, int stride, int offset);

private:
    GLuint m_hVAO;
};
} // namespace magic

#endif
