#ifndef _MAGIC_C_CAMERA_H_
#define _MAGIC_C_CAMERA_H_

#include "CComponent.h"
#include "render/IRenderTarget.h"

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

    /**
     * Camera will render to RenderTarget
     * **/
    void SetRenderTarget(IRenderTarget *pRenderTarget);
    IRenderTarget *GetRenderTarget();
    
};

} // namespace magic

#endif