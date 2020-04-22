#include "component/CMeshRendererComponent.h"
#include "render/CRenderInput.h"
#include "render/ERender.h"
#include "base/magicType.h"
#include "scene/ISceneNode.h"
#include "scene/IGameObject.h"

namespace magic
{
CMeshRendererComponent::CMeshRendererComponent()
:m_pMesh(nullptr)
,m_pMaterial(nullptr)
,m_pRenderer(nullptr)
,m_pRenderInput(nullptr)
,m_pMaterialInstance(new CMaterialInstance())
,m_Mode(GBM_TRIANGLES)
,m_Usage(GBU_DYNAMIC_DRAW)
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
        m_pRenderInput = pRenderer->CreateRenderInput(m_Mode, m_Usage);
        m_pMaterialInstance->Initialize(m_pRenderer, pMaterial);
        SetMaterial(pMaterial);
        SetMesh(pMesh);
    }
}

void CMeshRendererComponent::Update()
{
    m_pRenderer->SubmitToRenderQueue(m_pRenderInput);
}

void CMeshRendererComponent::OnTransformChanged(const CMatrix4 &worldMat)
{
    float *positions = m_pMesh->GetPositions();
    int vertCount = m_pMesh->GetVerticesCount();
    for (int i=0; i<vertCount; ++i)
    {
        CVector3 out;
        worldMat.TransformVect(out, CVector3(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]));
        positions[i * 3] = out.x;
        positions[i * 3 + 1] = out.y;
        positions[i * 3 + 2] = out.z;
    }
    SetMesh(m_pMesh);
    IShaderProgram *pShaderProgram = m_pMaterialInstance->GetShaderProgram();
    if (pShaderProgram)
    {
        ISceneNode *pNode = m_pGameObject->GetSceneNode();
        const CMatrix4 &mat = pNode->GetRelativeTransform();
        pShaderProgram->SetUniform("mMatrix", (void *)mat.m);
    }
}

void CMeshRendererComponent::SetMesh(IMesh *pMesh)
{
    //if (m_pMesh != pMesh)
    {
        m_pMesh = pMesh;
        if (m_pMesh)
        {                        
            int positionsSize = 0;
            int uvsSize = 0;
            int colorsSize = 0;
            int vertCount = m_pMesh->GetVerticesCount();
            float *positions = m_pMesh->GetPositions();
            float *uvs = m_pMesh->GetUVs();
            float *colors = m_pMesh->GetColors();
            
            m_pRenderInput->BeginInput(0, vertCount);
            
            if (positions)
                positionsSize = vertCount * sizeof(float) * 3;
            if (uvs)
                uvsSize = vertCount * sizeof(float) * 2;
            if (colors)
                colorsSize = vertCount * sizeof(float) * 4;
            m_pRenderInput->CreateVertexBufferObject(nullptr, positionsSize + colorsSize + uvsSize, m_Usage);
            if (positions)
                m_pRenderInput->SetVertexBuffer(positions, positionsSize, 0);
            if (uvs)
                m_pRenderInput->SetVertexBuffer(uvs, uvsSize, positionsSize);
            if (colors)
                m_pRenderInput->SetVertexBuffer(colors, colorsSize, positionsSize + uvsSize);
            
            unsigned short *indices = pMesh->GetIndices();
            if (indices)
            {
                m_pRenderInput->CreateIndexBufferObject(indices, pMesh->GetIndicesCount() * sizeof(unsigned short), m_Usage);
            }
            
            int index = 0;
            if (positionsSize > 0)
                m_pRenderInput->SetVertexAttribute(index++, 3, 0, 0);
            if (uvsSize > 0)
                m_pRenderInput->SetVertexAttribute(index++, 2, 0, positionsSize);
            if (colorsSize > 0)
                m_pRenderInput->SetVertexAttribute(index++, 4, 0, positionsSize + uvsSize);

            m_pRenderInput->EndInput();
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

}
