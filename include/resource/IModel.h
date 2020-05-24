#ifndef _MAGIC_I_MODEL_H_
#define _MAGIC_I_MODEL_H_

#include "IResource.h"
#include "IMesh.h"
#include "IMaterial.h"

namespace magic
{
class IModel : public IResource
{
public:
    virtual~IModel(){}
    virtual EResourceType GetType() const { return EResourceType::Model; }
    virtual void AddMesh(IMesh *pMesh) = 0;
    virtual IMesh *GetMesh(int index) const = 0;
    virtual int GetMeshCount() const = 0;
};
} // namespace magic

#endif
