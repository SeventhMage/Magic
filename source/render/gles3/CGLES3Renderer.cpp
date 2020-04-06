#include "CGLES3Renderer.h"
#include "CGLES3ShaderProgram.h"
#include "GLESDebug.h"


namespace magic
{
CGLES3Renderer::CGLES3Renderer(SRenderContext *esContextt, const char *title, GLint width, GLint height)
{
    //esCreateWindow(esContextt, title, width, height, flags);
}

void CGLES3Renderer::Render(IRenderInput *pRenderInput)
{
    IShaderProgram *pProgram = pRenderInput->GetShaderProgram();
    if (pProgram)
        pProgram->BindShaderParam();
    for (int i=0; i<pRenderInput->GetTextureCount(); ++i)
    {
        ITexture *pTexture = pRenderInput->GetTexture(i);
        if (pTexture)
            pTexture->BindTextureSlot(i);
    }
    IBufferObject *pIBO = pRenderInput->GetIndexBufferObject();
    if (pIBO)
    {
        GLDebug(glDrawElements(pIBO->GetMode(), pIBO->GetVerticesCount(), pIBO->GetValueType(), 0));
    }
    else
    {
        IBufferObject *pVBO = pRenderInput->GetVertexBufferObject();
        GLDebug(glDrawArrays(pVBO->GetMode(), pVBO->GetFirstIndex(), pVBO->GetVerticesCount()));
    }
    
}

IShaderProgram *CGLES3Renderer::CreateShaderProgram()
{
    return new CGLES3ShaderProgram();
}
}
