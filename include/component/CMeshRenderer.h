#ifndef _MAGIC_C_MESH_RENDERER_H_
#define _MAGIC_C_MESH_RENDERER_H_

#include "CComponent.h"
#include "scene/CMesh.h"
#include "scene/CMaterial.h"

namespace magic
{
class CMeshRenderer : CComponent
{
public:
    CMeshRenderer();
    virtual~CMeshRenderer();
private:
    CMesh *m_pMesh;
    CMaterial *m_pMaterial;
};
}

#endif