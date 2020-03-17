#include "CRenderer.h"

namespace magic
{
CRenderer::CRenderer()
{
}

void CRenderer::Render(IRenderInput *pRenderInput, IRenderTarget *pRenderTarget)
{
    IShaderProgram *pShaderProgram = pRenderInput->GetShaderProgram();
    pShaderProgram->BindShaderParam();

    ITexture *pTexture = pRenderInput->GetTexture();
    pTexture->BindTexture();

    IBuffer *pBuffer = pRenderInput->GetBuffer();
    pBuffer->BindBufferObject();
}
} // namespace magic