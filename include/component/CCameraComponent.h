#ifndef _MAGIC_C_CAMERA_H_
#define _MAGIC_C_CAMERA_H_

#include "CComponent.h"
#include "render/IRenderPass.h"
#include "render/IRenderer.h"

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

    void Initialize(IRenderer *pRenderer, CameraType type);
    void SetClearColor(float r, float g, float b, float a);
    void SetClearBit(int bit);
private:
    IRenderPass *m_pRenderPass;
    CameraType m_Type;
};

} // namespace magic

#endif
