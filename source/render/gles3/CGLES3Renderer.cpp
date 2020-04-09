#include "CGLES3Renderer.h"
#include "CGLES3ShaderProgram.h"
#include "GLESDebug.h"


namespace magic
{
CGLES3Renderer::CGLES3Renderer(SRenderContent *esContext, const char *title, GLint width, GLint height)
{
    //esCreateWindow(esContextt, title, width, height, flags);
}

void CGLES3Renderer::Render(IRenderInput *pRenderInput)
{
    IBufferObject *pVAO = pRenderInput->GetVertexArrayObject();
    pVAO->Bind();
    IShaderProgram *pProgram = pRenderInput->GetShaderProgram();
    if (pProgram)
        pProgram->Bind();
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

IRenderTarget *CGLES3Renderer::CreateRenderTarget(int width, int height, int format)
{

}

IShaderProgram *CGLES3Renderer::CreateShaderProgram()
{
    return new CGLES3ShaderProgram();
}
}
