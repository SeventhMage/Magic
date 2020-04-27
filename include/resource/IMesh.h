#ifndef _MAGIC_I_MESH_H_
#define _MAGIC_I_MESH_H_

#include "IResource.h"
#include "math/CVector4.h"
#include "math/CVector3.h"
#include "math/CVector2.h"


namespace magic
{
class IMesh : public IResource
{
public:
    virtual ~IMesh() {}
    virtual EResourceType GetType() const { return EResourceType::Mesh; }
    virtual float *GetPositions() const = 0;
    virtual float *GetColors() const = 0;
    virtual float *GetUVs() const = 0;
    virtual float *GetNormals() const = 0;
    virtual unsigned short *GetIndices() const = 0;
    virtual int GetVerticesCount() const = 0;
    virtual int GetIndicesCount() const = 0;
    
    virtual void SetPositions(float positions[][3], int size) = 0;
    virtual void SetUVs(float uvs[][2], int size) = 0;
    virtual void SetColors(float colors[][4], int size) = 0;
    virtual void SetIndices(const unsigned short *indices, int size) = 0;
    virtual void SetNormals(float normals[][3], int size) = 0;
};
} // namespace magic

#endif
