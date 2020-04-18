#include "resource/CMesh.h"
#include "base/magicDef.h"

#include <stdlib.h>

namespace magic
{
CMesh::CMesh()
:m_VerticesCount(0)
,m_IndicesCount(0)
,m_VerticesStride(0)
,m_Vertices(nullptr)
,m_Indices(nullptr)
{

}
CMesh::~CMesh()
{
    SAFE_DEL_ARRAY(m_Vertices);
    SAFE_DEL_ARRAY(m_Indices);
}

int CMesh::GetVerticesOffset(int index) const
{
    auto it = m_VerticesOffset.find(index);
    if (it != m_VerticesOffset.end())
    {
        return it->second;
    }
    return 0;
}

int CMesh::GetVerticesSize(int index) const
{
    auto it = m_VerticesSize.find(index);
    if (it != m_VerticesSize.end())
    {
        return it->second;
    }
    return 0;
}

void CMesh::SetIndices(const unsigned short *indices, int size)
{
    SAFE_DEL_ARRAY(m_Indices);
    m_Indices = new unsigned short[size];
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

void CMesh::SetVerticesOffset(int index, int offset)
{
    m_VerticesOffset[index] = offset;
}

void CMesh::SetVerticesStride(int stride)
{
    m_VerticesStride = stride;
}

void CMesh::SetVerticesSize(int index, int size)
{
    m_VerticesSize[index] = size;
}

}
