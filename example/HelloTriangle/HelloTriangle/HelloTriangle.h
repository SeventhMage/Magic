#ifndef _MAGIC_HELLO_TRIANGLE_H_
#define _MAGIC_HELLO_TRIANGLE_H_

#include "magic.h"
using namespace magic;
class HelloTriangle
{
public:
    HelloTriangle(SRenderContext *esContext);
    ~HelloTriangle();
private:
    void Init(SRenderContext *esContext);
    void InitDeferredShade(SRenderContext *esContext);
private:
    IMagic *mc;
    IRenderer *renderer;
    ISceneManager *sceneMgr;
    
    //triangle
    IMesh *triangleMesh;
    IMaterial *triangleMaterial;
    ITexture *triangleTexture;
    IRenderTarget *renderTarget;

    //deferred shade
    IMesh *deferredMesh;
    IMaterial *deferredMaterial;
    
    //screen aligned quad;
    IMesh *quadMesh;
    IMaterial *quadMaterial;
};

#endif /* HelloTriangle_h */
