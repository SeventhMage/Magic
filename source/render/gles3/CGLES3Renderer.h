#ifndef _MAGIC_C_GLES3RENDERER_H_
#define _MAGIC_C_GLES3RENDERER_H_

#include "../CRenderer.h"
#include "render/SRenderContext.h"

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
    CGLES3Renderer(SRenderContext *esContext, const char *title, GLint width, GLint height);
    virtual void SetClearColor(float r, float g, float b, float a);
    virtual void Clear(int flags);
    virtual IRenderTarget *CreateRenderTarget(int width, int height, int format);
    virtual IShaderProgram *CreateShaderProgram();
protected:
    virtual void Render(IRenderInput *pRenderInput);
private:
    bool Init(SRenderContext *esContext, const char *title, GLint width, GLint height);
};
} // namespace magic

#endif
