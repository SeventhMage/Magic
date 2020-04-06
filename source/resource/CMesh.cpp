#include "resource/CMesh.h"
#include "base/magicDef.h"

#include <stdlib.h>

namespace magic
{
CMesh::CMesh()
:m_Vertices(nullptr)
,m_Indices(nullptr)
,m_VerticesCount(0)
,m_IndicesCount(0)
,m_VerticesStride(0)
{

}
CMesh::~CMesh()
{
    SAFE_DEL_ARRAY(m_Vertices);
    SAFE_DEL_ARRAY(m_Indices);
}

void CMesh::SetIndices(const short *indices, int size)
{
    SAFE_DEL_ARRAY(m_Indices);
    m_Indices = new short[size];
    memcpy(m_Indices, indices, size);
    m_IndicesCount = size / sizeof(short);
}

void CMesh::SetVertices(const float *vertices, int size)
{
    SAFE_DEL_ARRAY(m_Vertices);
    m_Vertices = new float[size];
    memcpy(m_Vertices, vertices, size);
    m_VerticesCount = size / (sizeof(float) * 3);
}

int CMesh::GetVerticesOffset(int location) const
{
    auto it = m_VerticesOffset.find(location);
    if (it != m_VerticesOffset.end())
    {
        return it->second;
    }
    return 0;
}

void CMesh::SetVerticesOffset(int location, int offset)
{
    m_VerticesOffset[location] = offset;
}

void CMesh::SetVerticesStride(int stride)
{
    m_VerticesStride = stride;
}

}
