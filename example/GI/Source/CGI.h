#ifndef _MAGIC_C_GI_
#define _MAGIC_C_GI_

#include "magic.h"

namespace magic
{
class CGI
{
public:
    CGI();
    ~CGI();
    
    void Init(SRenderContext *context);
private:
    IMagic *mc;
    IRenderer *renderer;
    ISceneManager *sceneMgr;
    
    IRenderTarget *renderTarget;
    
    //box
    IMesh *boxMesh;
    IMaterial *boxMaterial;
    ITexture *boxTexture;
    
    //sphere
    IMesh *sphereMesh;
    IMaterial *sphereMaterial;
    ITexture *sphereTexture;
    
    //deferred shade
    IMesh *deferredMesh;
    IMaterial *deferredMaterial;
};
}

#endif
