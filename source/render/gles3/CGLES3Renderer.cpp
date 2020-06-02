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

#ifndef __APPLE__

///
// GetContextRenderableType()
//
//    Check whether EGL_KHR_create_context extension is supported.  If so,
//    return EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT
//
EGLint GetContextRenderableType(EGLDisplay eglDisplay)
{
#ifdef EGL_KHR_create_context
  const char *extensions = eglQueryString(eglDisplay, EGL_EXTENSIONS);

  // check whether EGL_KHR_create_context is in the extension string
  if (extensions != NULL && strstr(extensions, "EGL_KHR_create_context"))
  {
     // extension is supported
     return EGL_OPENGL_ES3_BIT_KHR;
  }
#endif
  // extension is not supported
  return EGL_OPENGL_ES2_BIT;
}
#endif

#ifdef WIN32
#include <Windows.h>
#include <WinUser.h>
LRESULT WINAPI ESWindowProc(HWND hWnd, ::UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  LRESULT lRet = 1;

  switch (uMsg)
  {
  case WM_CREATE:
     break;

  case WM_PAINT:
  {
	  SRenderContext *esContext = (SRenderContext *)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);

	  if (esContext && esContext->drawFunc)
	  {
		  if (esContext->drawFunc)
			  esContext->drawFunc();
	  }

     InvalidateRect(hWnd, NULL, false);
  }
  break;

  case WM_DESTROY:
     PostQuitMessage(0);
     break;

  case WM_CHAR:
  {
     POINT point;
     SRenderContext *esContext = (SRenderContext *)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);

     GetCursorPos(&point);

     if (esContext && esContext->keyFunc)
        esContext->keyFunc((unsigned char)wParam,
                           (int)point.x, (int)point.y);
  }
  break;

  default:
     lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
     break;
  }

  return lRet;
}

GLboolean WinCreate(SRenderContext *esContext, const char *title)
{
  WNDCLASS wndclass = {0};
  DWORD wStyle = 0;
  RECT windowRect;
  HINSTANCE hInstance = GetModuleHandle(NULL);

  wndclass.style = CS_OWNDC;
  wndclass.lpfnWndProc = (WNDPROC)ESWindowProc;
  wndclass.hInstance = hInstance;
  wndclass.hbrBackground = NULL;
  wndclass.lpszClassName = title;

  if (!RegisterClass(&wndclass))
  {
     LogError("RegisterClass failed.\n");
     return FALSE;
  }

  wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

  // Adjust the window rectangle so that the client area has
  // the correct number of pixels
  windowRect.left = 0;
  windowRect.top = 0;
  windowRect.right = esContext->width;
  windowRect.bottom = esContext->height;

  AdjustWindowRect(&windowRect, wStyle, FALSE);

  esContext->eglNativeWindow = CreateWindow(
      title,
      title,
      wStyle,
      0,
      0,
      windowRect.right - windowRect.left,
      windowRect.bottom - windowRect.top,
      NULL,
      NULL,
      hInstance,
      NULL);

  // Set the ESContext* to the GWL_USERDATA so that it is available to the
  // ESWindowProc
#ifdef _WIN64
  //In LLP64 LONG is stll 32bit.
  SetWindowLongPtr(esContext->eglNativeWindow, GWL_USERDATA, (LONGLONG)(LONG_PTR)esContext);
#else
  SetWindowLongPtr(esContext->eglNativeWindow, GWL_USERDATA, (LONG)(LONG_PTR)esContext);
#endif

  if (esContext->eglNativeWindow == NULL)
  {
     LogError("esContext->eglNativeWindow == NULL.\n");
     return GL_FALSE;
  }

  ShowWindow(esContext->eglNativeWindow, TRUE);
  esContext->eglNativeDisplay = GetDC(esContext->eglNativeWindow);

  return GL_TRUE;
}

#endif

CGLES3Renderer::CGLES3Renderer(SRenderContext *esContext, const char *title, GLint width, GLint height)
: m_esContext(esContext)
,m_FinalRenderTarget(nullptr)
{
    if (!Init(esContext, title, width, height))
        LogError("Initialize GLES3Renderer failed\n");
    GLDebug(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_defaultFrameBuffer));
    float ratio = esContext->screenResolutionRatio > 0 ? esContext->screenResolutionRatio : 1.f;
    m_FinalRenderTarget = CreateRenderTarget(esContext->width * ratio, esContext->height * ratio, true);
}

CGLES3Renderer::~CGLES3Renderer()
{
#ifdef WIN32
    ReleaseDC(m_esContext->eglNativeWindow, m_esContext->eglNativeDisplay);
#endif
    SAFE_DEL(m_FinalRenderTarget);
}

void CGLES3Renderer::SetClearColor(float r, float g, float b, float a)
{
  GLDebug(glClearColor(r, g, b, a));
}

void CGLES3Renderer::Clear(int flags)
{
  GLDebug(glClear(GetGLColorMask(flags)));
}

IRenderTarget *CGLES3Renderer::CreateRenderTarget(int width, int height, bool haveDepth, int textureCount)
{
  return new CGLES3RenderTarget(textureCount, width, height, haveDepth);
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
      LogError("CGLES3Renderer::Init SRenderContext is null.\n");
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
        LogError("WinCreate failed.\n");
        return GL_FALSE;
    }

    esContext->eglDisplay = eglGetDisplay(esContext->eglNativeDisplay);
    if (esContext->eglDisplay == EGL_NO_DISPLAY)
    {
        LogError("eglDisplay == EGL_NO_DISPLAY.\n");
        return GL_FALSE;
    }

    // Initialize EGL
    if (!eglInitialize(esContext->eglDisplay, &majorVersion, &minorVersion))
    {
        LogError("eglInitialize failed.\n");
        return GL_FALSE;
    }

    {
        EGLint numConfigs = 0;
        EGLint attribList[] =
        {
            EGL_RED_SIZE, 5,
            EGL_GREEN_SIZE, 6,
            EGL_BLUE_SIZE, 5,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_STENCIL_SIZE, 8,
            EGL_SAMPLE_BUFFERS, 1,
             // if EGL_KHR_create_context extension is supported, then we will use
             // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
            EGL_RENDERABLE_TYPE, GetContextRenderableType(esContext->eglDisplay),
            EGL_NONE};

        // Choose config
        if (!eglChooseConfig(esContext->eglDisplay, attribList, &config, 1, &numConfigs))
        {
            LogError("eglChooseConfig failed.\n");
            return GL_FALSE;
        }

        if (numConfigs < 1)
        {
            LogError("eglChooseConfig numConfigs < 1.\n");
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
        LogError("eglContext == EGL_NO_CONTEXT\n");
        return GL_FALSE;
    }

    // Make the context current
    if (!eglMakeCurrent(esContext->eglDisplay, esContext->eglSurface,
                      esContext->eglSurface, esContext->eglContext))
    {
        LogError("eglMakeCurrent failed.\n");
        return GL_FALSE;
    }

#endif // #ifndef __APPLE__
    return GL_TRUE;
}

IBufferObject *CGLES3Renderer::CreateVertexArrayObject()
{
    return new CGLES3VertexArrayObject();
}

IBufferObject *CGLES3Renderer::CreateVertexBufferObject(void *vertices, int size, int usage)
{
    return new CGLES3VertexBufferObject(vertices, size, usage);
}

IBufferObject *CGLES3Renderer::CreateIndexBufferObject(void *indices, int size, int usage)
{
    return new CGLES3IndexBufferObject(indices, size, usage);
}

void CGLES3Renderer::Render(IRenderInput *pRenderInput, IRenderPass *pRenderPass)
{
    //glViewport ( 0, 0, m_esContext->width, m_esContext->height );
    GLDebug(glEnable(GL_DEPTH_TEST));
    CVertexArrayObject *pVAO = (CVertexArrayObject *)pRenderInput->GetVertexArrayObject();
    pVAO->Bind();
    for (int i = 0; i < pRenderInput->GetTextureCount(); ++i)
    {
        ITexture *pTexture = pRenderInput->GetTexture(i);
        if (pTexture)
            pTexture->Bind(i);
    }
    IShaderProgram *pProgram = pRenderInput->GetShaderProgram();
    for (int i = 0; i < pRenderPass->GetShaderParamCount(); ++i)
        pProgram->SetUniform(pRenderPass->GetShaderParam(i)->paramName, pRenderPass->GetShaderParam(i)->paramData);
    pProgram->Bind();

    CIndexBufferObject *pIBO = (CIndexBufferObject *)pRenderInput->GetIndexBufferObject();
    if (pIBO)
    {
        pIBO->Bind();
        GLDebug(glDrawElements(GetGLGPUBufferMode((GPUBufferMode)pRenderInput->GetMode()), pRenderInput->GetIndicesCount(), GetGLVariableType((VariableType)pRenderInput->GetIndexType()), 0));
        pIBO->UnBind();
    }
    else
    {
        GLDebug(glDrawArrays(GetGLGPUBufferMode((GPUBufferMode)pRenderInput->GetMode()), pRenderInput->GetFirst(), pRenderInput->GetVerticesCount()));
    }
    for (int i = 0; i < pRenderInput->GetTextureCount(); ++i)
    {
        ITexture *pTexture = pRenderInput->GetTexture(i);
        if (pTexture)
            pTexture->UnBind();
    }
    pVAO->UnBind();
}

ITexture *CGLES3Renderer::CreateTexture(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data)
{
   ITexture *pTexture = new CGLES3Texture();
   pTexture->Create2D(internalformat, width, height, format, type, data);
   return pTexture;
}

void CGLES3Renderer::FinalRender()
{
    if (m_FinalRenderTarget)
    {
        GLDebug(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_defaultFrameBuffer));
        GLDebug(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FinalRenderTarget->GetFrameBufferObject()));
        //GLDebug(glReadBuffer(GL_COLOR_ATTACHMENT0));
        GLDebug(glBlitFramebuffer(0, 0, m_FinalRenderTarget->GetWidth(), m_FinalRenderTarget->GetHeight(), 0, 0, m_esContext->width, m_esContext->height, GL_COLOR_BUFFER_BIT, GL_LINEAR));
    }
#ifndef __APPLE__
    eglSwapBuffers(m_esContext->eglDisplay, m_esContext->eglSurface);
#endif
}

void CGLES3Renderer::Viewport(int x, int y, int width, int height)
{
    GLDebug(glViewport(x, y, width, height));
}

void CGLES3Renderer::BeginFinalRenderTarget()
{
    if (m_FinalRenderTarget)
    {
        m_FinalRenderTarget->BeginTarget();
        Viewport(0, 0, m_FinalRenderTarget->GetWidth(), m_FinalRenderTarget->GetHeight());
    }
    else
    {
        GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFrameBuffer));
        Viewport(0, 0, m_esContext->width, m_esContext->height);
    }
}

void CGLES3Renderer::EndFinalRenderTarget()
{
    if (m_FinalRenderTarget)
        m_FinalRenderTarget->EndTarget();
}

} // namespace magic
