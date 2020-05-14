#ifndef _MAGIC_C_GLES3_VERTEX_ARRAY_OBJECT_H_
#define _MAGIC_C_GLES3_VERTEX_ARRAY_OBJECT_H_

#include "../CVertexArrayObject.h"
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

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
