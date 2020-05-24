#include "resource/CModel.h"
#include "resource/CMesh.h"
#include "resource/CMaterial.h"
#include "base/magicDef.h"

namespace magic
{
CModel::CModel()
{

}

CModel::~CModel()
{
    
}

void CModel::AddMesh(IMesh *pMesh)
{
    m_MeshVec.push_back(pMesh);
}

IMesh *CModel::GetMesh(int index) const
{
    if (index >=0 && index < m_MeshVec.size())
    {
        return m_MeshVec[index];
    }
    return nullptr;
}

}
