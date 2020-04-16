#include "CGLES3Renderer.h"
#include "CGLES3ShaderProgram.h"
#include "CGLES3RenderTarget.h"
#include "CGLES3VertexArrayObject.h"
#include "CGLES3VertexBufferObject.h"
#include "CGLES3IndexBufferObject.h"
#include "GLESDebug.h"
#include "GLESType.h"
#include "base/Log.h"

namespace magic
{
CGLES3Renderer::CGLES3Renderer(SRenderContext *esContext, const char *title, GLint width, GLint height)
{
   if (Init(esContext, title, width, height))
      LogError("Initialize GLES3Renderer failed");
}

void CGLES3Renderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void CGLES3Renderer::Clear(int flags)
{
    glClear(GetGLColorMask(flags));
}

void CGLES3Renderer::Render(IRenderInput *pRenderInput)
{
   CVertexArrayObject *pVAO = (CVertexArrayObject *)pRenderInput->GetVertexArrayObject();
   pVAO->Bind();
   IShaderProgram *pProgram = pRenderInput->GetShaderProgram();
   if (pProgram)
      pProgram->Bind();
   for (int i = 0; i < pRenderInput->GetTextureCount(); ++i)
   {
      ITexture *pTexture = pRenderInput->GetTexture(i);
      if (pTexture)
         pTexture->Bind(i);
   }
   CIndexBufferObject *pIBO = (CIndexBufferObject *)pRenderInput->GetIndexBufferObject();
   if (pIBO)
   {
     // GLDebug(glDrawElements(pIBO->GetMode(), pIBO->GetVerticesCount(), pIBO->GetValueType(), 0));
   }
   else
   {
      CVertexBufferObject *pVBO = (CVertexBufferObject *)pRenderInput->GetVertexBufferObject();
      GLDebug(glDrawArrays(pVBO->GetMode(), pVBO->GetFirstIndex(), pVBO->GetVerticesCount()));
   }
}

IRenderTarget *CGLES3Renderer::CreateRenderTarget(int width, int height, int format)
{
   return new CGLES3RenderTarget(1, width, height, false);
}

IShaderProgram *CGLES3Renderer::CreateShaderProgram()
{
   return new CGLES3ShaderProgram();
}

bool CGLES3Renderer::Init(SRenderContext *esContext, const char *title, GLint width, GLint height)
{
#ifndef __APPLE__
   EGLConfig config;
   EGLint majorVersion;
   EGLint minorVersion;
   EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

   if (esContext == NULL)
   {
      return GL_FALSE;
   }

#ifdef ANDROID
   // For Android, get the width/height from the window rather than what the
   // application requested.
   esContext->width = ANativeWindow_getWidth(esContext->eglNativeWindow);
   esContext->height = ANativeWindow_getHeight(esContext->eglNativeWindow);
#else
   esContext->width = width;
   esContext->height = height;
#endif

   if (!WinCreate(esContext, title))
   {
      return GL_FALSE;
   }

   esContext->eglDisplay = eglGetDisplay(esContext->eglNativeDisplay);
   if (esContext->eglDisplay == EGL_NO_DISPLAY)
   {
      return GL_FALSE;
   }

   // Initialize EGL
   if (!eglInitialize(esContext->eglDisplay, &majorVersion, &minorVersion))
   {
      return GL_FALSE;
   }

   {
      EGLint numConfigs = 0;
      EGLint attribList[] =
          {
              EGL_RED_SIZE, 5,
              EGL_GREEN_SIZE, 6,
              EGL_BLUE_SIZE, 5,
              EGL_ALPHA_SIZE, 8 ,
              EGL_DEPTH_SIZE, 8,
              EGL_STENCIL_SIZE, 8,
              EGL_SAMPLE_BUFFERS,1,
              // if EGL_KHR_create_context extension is supported, then we will use
              // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
              EGL_RENDERABLE_TYPE, GetContextRenderableType(esContext->eglDisplay),
              EGL_NONE};

      // Choose config
      if (!eglChooseConfig(esContext->eglDisplay, attribList, &config, 1, &numConfigs))
      {
         return GL_FALSE;
      }

      if (numConfigs < 1)
      {
         return GL_FALSE;
      }
   }

#ifdef ANDROID
   // For Android, need to get the EGL_NATIVE_VISUAL_ID and set it using ANativeWindow_setBuffersGeometry
   {
      EGLint format = 0;
      eglGetConfigAttrib(esContext->eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format);
      ANativeWindow_setBuffersGeometry(esContext->eglNativeWindow, 0, 0, format);
   }
#endif // ANDROID

   // Create a surface
   esContext->eglSurface = eglCreateWindowSurface(esContext->eglDisplay, config,
                                                  esContext->eglNativeWindow, NULL);

   if (esContext->eglSurface == EGL_NO_SURFACE)
   {
      return GL_FALSE;
   }

   // Create a GL context
   esContext->eglContext = eglCreateContext(esContext->eglDisplay, config,
                                            EGL_NO_CONTEXT, contextAttribs);

   if (esContext->eglContext == EGL_NO_CONTEXT)
   {
      return GL_FALSE;
   }

   // Make the context current
   if (!eglMakeCurrent(esContext->eglDisplay, esContext->eglSurface,
                       esContext->eglSurface, esContext->eglContext))
   {
      return GL_FALSE;
   }

#endif // #ifndef __APPLE__
    return GL_TRUE;
}

IBufferObject *CGLES3Renderer::CreateVertexArrayObject()
{
    return new CGLES3VertexArrayObject();
}

IBufferObject *CGLES3Renderer::CreateVertexBufferObject(void *vertexes, int size, int usage, int first, int count, int mode)
{
    return new CGLES3VertexBufferObject(vertexes, size, usage, first, count, mode);
}

IBufferObject *CGLES3Renderer::CreateIndexBufferObject(void *indices, int idsCount, int idsType, int mode, int usage)
{
    return new CGLES3IndexBufferObject(indices, idsCount, idsType, mode, usage);
}

} // namespace magic
