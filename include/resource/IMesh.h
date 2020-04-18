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
    virtual float *GetVertices() const = 0;
    virtual unsigned short *GetIndices() const = 0;
    virtual int GetVerticesCount() const = 0;
    virtual int GetIndicesCount() const = 0;
    virtual int GetVerticesStride() const = 0;
    virtual int GetVerticesOffset(int index) const = 0;
    virtual int GetVerticesSize(int index) const = 0;
    virtual int GetVerticesAttributeCount() const = 0;

    virtual void SetVertices(const float *vertices, int size) = 0;
    virtual void SetIndices(const unsigned short *indices, int size) = 0;
    virtual void SetVerticesStride(int stride) = 0;
    virtual void SetVerticesOffset(int index, int offset) = 0;
    virtual void SetVerticesSize(int index, int offset) = 0;
};
} // namespace magic

#endif
