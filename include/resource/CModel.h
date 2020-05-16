#ifndef _MAGIC_C_MODEL_H_
#define _MAGIC_C_MODEL_H_

#include "IModel.h"
#include "IMesh.h"
#include "IMaterial.h"

namespace magic
{
class CModel : public IModel
{
public:
    CModel();
    virtual ~CModel();
    
    virtual bool Load(const char *path);
private:
    IMesh *m_pMesh;
    IMaterial *m_pMaterial;
};
}

#endif
