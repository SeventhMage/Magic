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
    virtual ~CGLES3Renderer();
    virtual void SetClearColor(float r, float g, float b, float a);
    virtual void Clear(int flags);
    virtual IRenderTarget *CreateRenderTarget(int width, int height, bool haveDepth = false, int textureCout = 1);
    virtual IShaderProgram *CreateShaderProgram();
    virtual IBufferObject *CreateVertexArrayObject();
    virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size, int usage);
    virtual IBufferObject *CreateIndexBufferObject(void *indices, int size, int usage);
    virtual ITexture *CreateTexture(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data);
    virtual void Viewport(int x, int y, int width, int height);
    virtual int GetWindowWidth() const { return m_esContext->width; }
    virtual int GetWindowHeight() const { return m_esContext->height; }
    virtual void BeginFinalRenderTarget();
    virtual void EndFinalRenderTarget();
    virtual IRenderTarget *GetFinalRenderTarget() { return m_FinalRenderTarget; }
protected:
    virtual void Render(IRenderInput *pRenderInput, IRenderPass *pRenderPass);
    virtual void FinalRender();
private:
    bool Init(SRenderContext *esContext, const char *title, GLint width, GLint height);
private:
    SRenderContext *m_esContext;
    IRenderTarget *m_FinalRenderTarget;
    GLint m_defaultFrameBuffer;
};
} // namespace magic

#endif
