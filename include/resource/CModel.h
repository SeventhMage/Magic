#ifndef _MAGIC_C_MODEL_H_
#define _MAGIC_C_MODEL_H_

#include "IModel.h"
#include "IMesh.h"

#include <vector>

namespace magic
{
class CModel : public IModel
{
public:
    CModel();
    virtual ~CModel();
    virtual void AddMesh(IMesh *pMesh);
    virtual IMesh *GetMesh(int index) const;
    virtual int GetMeshCount() const { return (int)m_MeshVec.size(); }
private:
    std::vector<IMesh *>m_MeshVec;
};
}

#endif
