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
    //需要手动控件销毁顺序，保证在引擎销毁前删除
    CGameObject *triangle;
    CGameObject *triangleCamera;
    

    //deferred shade
    IMesh *deferredMesh;
    IMaterial *deferredMaterial;
    CGameObject *deferredCamera;
    CGameObject *deferredObject;
    IRenderTarget *screenTarget;
    
    //screen aligned quad;
    IMesh *quadMesh;
    IMaterial *quadMaterial;
    CGameObject *quadCamera;
    CGameObject *screenAlignedQuad;
};

#endif /* HelloTriangle_h */
