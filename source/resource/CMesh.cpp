#include "resource/CMesh.h"
#include "base/magicDef.h"

#include <stdlib.h>

namespace magic
{
CMesh::CMesh()
:m_VerticesCount(0)
,m_IndicesCount(0)
,m_Vertices(nullptr)
,m_Positions(nullptr)
,m_Colors(nullptr)
,m_Uvs(nullptr)
,m_Indices(nullptr)
{

}
CMesh::~CMesh()
{
    SAFE_DEL_ARRAY(m_Vertices);
    SAFE_DEL_ARRAY(m_Indices);
}

void CMesh::SetIndices(const unsigned short *indices, int size)
{
    SAFE_DEL_ARRAY(m_Indices);
    m_Indices = new unsigned short[size];
    memcpy(m_Indices, indices, size);
    m_IndicesCount = size / sizeof(unsigned short);
}

void CMesh::SetPositions(float positions[][3], int size)
{
    SAFE_DEL_ARRAY(m_Positions);
    m_VerticesCount = size / (sizeof(float) * 3);
    m_Positions = new float[size / sizeof(float)];
    memcpy(m_Positions, positions, size);
}

void CMesh::SetUVs(float uvs[][2], int size)
{
    SAFE_DEL_ARRAY(m_Uvs);
    m_Uvs = new float[size / sizeof(float)];
    memcpy(m_Uvs, uvs, size);
}

void CMesh::SetColors(float colors[][4], int size)
{
    SAFE_DEL_ARRAY(m_Colors);
    m_Colors = new float[size / sizeof(float)];
    memcpy(m_Colors, colors, size);
}

}
