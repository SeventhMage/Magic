#include "render/CMaterialInstance.h"

namespace magic
{
CMaterialInstance::CMaterialInstance()
:m_pShaderProgram(nullptr)
{
}

CMaterialInstance::~CMaterialInstance()
{
    SAFE_DEL(m_pShaderProgram);
}

void CMaterialInstance::Initialize(IRenderer *pRenderer, IMaterial *pMaterial)
{
    m_pShaderProgram = pRenderer->CreateShaderProgram();
    for (int i=0; i<EShaderType::Count; ++i)
    {
        IShader *pShader = pMaterial->GetShader((EShaderType)i);
        if (pShader)
            m_pShaderProgram->Attach(pShader);
    }

    for (int i=0; i< pMaterial->GetAttributeCount(); ++i)
    {
        m_pShaderProgram->BindAttributeLocation(i, pMaterial->GetAttributeName(i));
    }
    m_pShaderProgram->Link();
}


}
