#include "component/CMeshRendererComponent.h"
#include "render/CRenderInput.h"
#include "base/magicType.h"

namespace magic
{
CMeshRendererComponent::CMeshRendererComponent()
:m_pMesh(nullptr)
,m_pMaterial(nullptr)
,m_pRenderer(nullptr)
,m_pRenderInput(nullptr)
,m_pMaterialInstance(new CMaterialInstance())
{
}

CMeshRendererComponent::~ CMeshRendererComponent()
{
    SAFE_DEL(m_pRenderInput);
    SAFE_DEL(m_pMaterialInstance);
    
}

void CMeshRendererComponent::Initialize(IRenderer *pRenderer, IMaterial *pMaterial, IMesh *pMesh)
{
    m_pRenderer = pRenderer;
    if (m_pRenderer)
    {
        m_pRenderInput = pRenderer->CreateRenderInput();
        m_pMaterialInstance->Initialize(m_pRenderer, pMaterial);
        SetMaterial(pMaterial);
        SetMesh(pMesh);
    }
}

void CMeshRendererComponent::Update()
{
    m_pRenderer->SubmitToRenderQueue(m_pRenderInput);
}

void CMeshRendererComponent::SetMesh(IMesh *pMesh)
{
    if (m_pMesh != pMesh)
    {
        m_pMesh = pMesh;
        if (m_pMesh)
        {
            for (int i=0; i<m_pMesh->GetVerticesAttributeCount(); ++i)
                m_pRenderInput->SetVertexAttribute(i, m_pMesh->GetVerticesOffset(i), 
                    m_pMesh->GetVerticesStride(), m_pMesh->GetVerticesOffset(i));
            //m_pRenderInput->SetVertexBuffer(m_pMesh->GetVertices(), m_pMesh->GetVerticesCount() * sizeof(float));
            //m_pRenderInput->SetIndexBuffer(pMesh->GetIndices(), m_pMesh->GetIndicesCount() * sizeof(float));
        }
    }
}

void CMeshRendererComponent::SetMaterial(IMaterial *pMaterial)
{
    if (m_pMaterial != pMaterial)
    {
        m_pMaterial = pMaterial;
        if (m_pRenderer && m_pMaterial)
        {
            m_pMaterialInstance->Initialize(m_pRenderer, m_pMaterial);
            m_pRenderInput->SetRenderQueue(m_pMaterial->GetID());
            m_pRenderInput->SetShaderProgram(m_pMaterialInstance->GetShaderProgram());
        }
    }
}

void CMeshRendererComponent::SubmitRenderInput()
{
    m_pRenderer->SubmitToRenderQueue(m_pRenderInput);
}

}
