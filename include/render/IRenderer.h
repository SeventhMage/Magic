#ifndef _MAGIC__RENDER_RENDERER_H_
#define _MAGIC__RENDER_RENDERER_H_

#include "IRenderInput.h"
#include "IRenderTarget.h"
#include "IRenderPass.h"
#include "IShaderProgram.h"
#include "IBufferObject.h"
#include "ERender.h"
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
    virtual IRenderPass *GenerateRenderPass() = 0;
    virtual void DestroyRenderPass(IRenderPass *) = 0;
    virtual void SubmitToRenderQueue(IRenderInput *pInput) = 0;
    virtual void Render() = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;
    virtual void Clear(int flags) = 0;
    virtual void Viewport(int x, int y, int width, int height) = 0;
    virtual IRenderTarget *CreateRenderTarget(int width, int height, bool haveDepth = false, int textureCount = 1) = 0;
    virtual IRenderInput *CreateRenderInput(int mode, int usage) = 0;
    virtual IShaderProgram *CreateShaderProgram() = 0;
    virtual IBufferObject *CreateVertexArrayObject() = 0;
    virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size, int usage) = 0;
    virtual IBufferObject *CreateIndexBufferObject(void *indices, int size, int usage) = 0;
    virtual ITexture *CreateTexture(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data) = 0;
    virtual int GetWindowWidth() const = 0;
    virtual int GetWindowHeight() const = 0;
    virtual void BeginFinalRenderTarget() = 0;
    virtual void EndFinalRenderTarget() = 0;
    virtual IRenderTarget *GetFinalRenderTarget() = 0;
};
} // namespace magic

#endif
