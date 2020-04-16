#ifndef _MAGIC_S_RENDER_CONTENT_H_
#define _MAGIC_S_RENDER_CONTENT_H_

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

namespace magic
{
struct SRenderContext
{
    /// Put platform specific data here
    void *platformData;

    /// Put your user data here...
    void *userData;

    /// Window width
    int width;

    /// Window height
    int height;

#ifndef __APPLE__
    /// Display handle
    EGLNativeDisplayType eglNativeDisplay;

    /// Window handle
    EGLNativeWindowType eglNativeWindow;

    /// EGL display
    EGLDisplay eglDisplay;

    /// EGL context
    EGLContext eglContext;

    /// EGL surface
    EGLSurface eglSurface;
#endif
    void ( *drawFunc ) ( SRenderContext * );
    void ( *shutdownFunc ) ();
    void ( *keyFunc ) ( SRenderContext *, unsigned char, int, int );
    void ( *updateFunc ) ();
};
} // namespace magic

#endif
