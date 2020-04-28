#ifndef _MAGIC_C_CAMERA_H_
#define _MAGIC_C_CAMERA_H_

#include "CComponent.h"
#include "render/IRenderPass.h"
#include "render/IRenderer.h"
#include "render/IRenderTarget.h"
#include "math/CMatrix4.h"
#include "math/CFrustum.h"

namespace magic
{
class CCameraComponent : public CComponent
{
public:
    enum CameraType
    {
        Projection,
        Ortho,
    };
    CCameraComponent();
    ~CCameraComponent();

    virtual void Update();
    virtual void OnTransformChanged(const CMatrix4 &wordMat);

    void Initialize(IRenderer *pRenderer, CameraType type, float fov, float aspect, float near, float far);
    void SetClearColor(float r, float g, float b, float a);
    void SetClearBit(int bit);
    void SetRenderTarget(IRenderTarget *target);
private:
    IRenderPass *m_pRenderPass;
    IRenderer *m_pRenderer;
    CameraType m_Type;
    CMatrix4 m_vpMatrix;
    CMatrix4 m_viewMatrix;
    CMatrix4 m_projMatrix;
    CFrustum m_frustum;
    
    uint m_Width;
    uint m_Height;
    
    float m_FarClip;
    float m_NearClip;
    float m_Fov;
    float m_Aspect;
    
    bool m_bNeedUpdateView;
    bool m_bNeedUpdateProj;
};

} // namespace magic

#endif
