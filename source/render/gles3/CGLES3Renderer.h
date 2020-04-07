#ifndef _MAGIC_C_GLES3RENDERER_H_
#define _MAGIC_C_GLES3RENDERER_H_

#include "render/CRenderer.h"
#include "render/SRenderContent.h"
#include "gl3.h"

/*
#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif
*/

namespace magic
{
class CGLES3Renderer : public CRenderer
{
public:
    CGLES3Renderer(SRenderContent *esContext, const char *title, GLint width, GLint height);
    virtual IShaderProgram *CreateShaderProgram();
protected:
    virtual void Render(IRenderInput *pRenderInput);
};
} // namespace magic

#endif