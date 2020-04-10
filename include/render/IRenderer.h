#ifndef _MAGIC__RENDER_RENDERER_H_
#define _MAGIC__RENDER_RENDERER_H_

#include "IRenderInput.h"
#include "IRenderTarget.h"
#include "IShaderProgram.h"
#include "math/CMatrix4.h"

namespace magic
{
class IRenderer
{
public:
    virtual ~IRenderer(){}
    /**
     * Each camera will create a render pass
     * **/
    virtual void CreateRenderPass(const CMatrix4 &viewProjMatrix) = 0;
    virtual void SubmitToRenderQueue(IRenderInput *pInput) = 0;
    virtual void Render() = 0;
    virtual IRenderTarget *CreateRenderTarget(int width, int height, int format) = 0;
    virtual IRenderInput *CreateRenderInput();
    virtual IShaderProgram *CreateShaderProgram() = 0;
};
} // namespace magic

#endif