#ifndef _MAGIC_C_MESH_RENDERER_H_
#define _MAGIC_C_MESH_RENDERER_H_

#include "CComponent.h"
#include "resource/IMesh.h"
#include "resource/IMaterial.h"
#include "render/IRenderer.h"
#include "render/CMaterialInstance.h"

namespace magic
{
class CMeshRendererComponent : public CComponent
{
public:
    CMeshRendererComponent();
    virtual~ CMeshRendererComponent();
    
    virtual void Update();
    virtual void OnTransformChanged(const CMatrix4 &worldMat);
    void Initialize(IRenderer *pRenderer, IMaterial *pMaterial, IMesh *pMesh);
    void SetMesh(IMesh *pMesh);
    void SetMaterial(IMaterial *pMaterial);
private:
    IMesh *m_pMesh;
    IMaterial *m_pMaterial;
    IRenderer *m_pRenderer;
    IRenderInput *m_pRenderInput;
    CMaterialInstance *m_pMaterialInstance;
    int m_Mode;
    int m_Usage;
};
}

#endif
