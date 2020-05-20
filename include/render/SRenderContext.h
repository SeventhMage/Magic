#ifndef _MAGIC_S_RENDER_CONTENT_H_
#define _MAGIC_S_RENDER_CONTENT_H_

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#include <functional>

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
    
    /// Screen resolution ratio
    float screenResolutionRatio;
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
//    void ( *drawFunc ) ( SRenderContext * );
//    void ( *shutdownFunc ) ();
//    void ( *keyFunc ) ( SRenderContext *, unsigned char, int, int );
//    void ( *updateFunc ) ();
    
    std::function<void()> drawFunc;
    std::function<void()> updateFunc;
    std::function<void()> shutdownFunc;
    std::function<void(unsigned char, int, int)> keyFunc;
    std::function<void(int index, int x, int y, int count)> touchFunc;
    std::function<void(int index, int x, int y, int count)> touchMoveFunc;
    
    bool bInitalize;
};
} // namespace magic

#endif
