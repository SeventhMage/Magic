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
    IRenderTarget *vplTarget;
    IRenderTarget *indirectTarget;
    
    //box
    IMesh *boxMesh;
    IMaterial *boxMaterial;
    ITexture *boxTexture;
    
    //sphere
    IMesh *sphereMesh;
    IMaterial *sphereMaterial;
    ITexture *sphereTexture;
    
    //virtual point light generate
    IMesh *vplMesh;
    IMesh *vplMaterial;
    
    //deferred shade
    IMesh *deferredMesh;
    IMaterial *deferredMaterial;
    
    //indirect light
    IMesh *indirectMesh;
    IMaterial *indirectMaterial;
};
}

#endif
