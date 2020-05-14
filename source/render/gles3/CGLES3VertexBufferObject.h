#ifndef _MAGIC_CGLES3VERTEXBUFFEROBJECT_H_
#define _MAGIC_CGLES3VERTEXBUFFEROBJECT_H_

#include "../CVertexBufferObject.h"
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

namespace magic
{
class CGLES3VertexBufferObject : public CVertexBufferObject
{
public:
    CGLES3VertexBufferObject(void *vertices, int size, int usage);
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
