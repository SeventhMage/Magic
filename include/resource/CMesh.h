#ifndef _MAGIC_C_MESH_H_
#define _MAGIC_C_MESH_H_

#include "IMesh.h"

#include <map>

namespace magic
{
class CMesh : public IMesh
{
public:
    CMesh();
    virtual ~CMesh();
    virtual float *GetVertices() const {return m_Vertices;}
    virtual short *GetIndices() const {return m_Indices; }
    virtual int GetVerticesCount() const {return m_VerticesCount;}
    virtual int GetIndicesCount() const {return m_IndicesCount;}
    virtual int GetVerticesStride() const { return m_VerticesStride; }
    virtual int GetVerticesOffset(int index) const;
    virtual int GetVerticesSize(int index) const;
    virtual int GetVerticesAttributeCount() const { return m_VerticesOffset.size(); }

    virtual void SetVertices(const float *vertices, int size);
    virtual void SetIndices(const short *indices, int size);
    virtual void SetVerticesStride(int stride);
    virtual void SetVerticesOffset(int index, int offset);
    virtual void SetVerticesSize(int index, int offset);
private:
    int m_VerticesCount;
    int m_IndicesCount;
    int m_VerticesStride;
    float *m_Vertices;
    short *m_Indices;
    std::map<int, int> m_VerticesOffset;
    std::map<int, int> m_VerticesSize;
};
} // namespace magic

#endif /* CMesh_h */