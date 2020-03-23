#ifndef _MAGIC_C_GLES3RENDERER_H_
#define _MAGIC_C_GLES3RENDERER_H_

#include "../CRenderer.h"
#include "esUtil.h"

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

namespace magic
{
class CGLES3Renderer : public CRenderer
{
public:
    CGLES3Renderer(void *esContext, const char *title, GLint width, GLint height, GLuint flags);
    virtual void SubmitToRenderQueue(IRenderInput *pInput, int materialId){}
    virtual void Render(IRenderInput *pRenderInput, IRenderTarget *pRenderTarget){}
    virtual void Render(){}
};
} // namespace magic

#endif
