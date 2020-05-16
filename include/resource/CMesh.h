#ifndef _MAGIC_C_MESH_H_
#define _MAGIC_C_MESH_H_

#include "IMesh.h"

#include <map>
#include <string>

namespace magic
{
class CMesh : public IMesh
{
public:
    CMesh(const char *fileName = "");
    virtual ~CMesh();
    virtual float *GetPositions() const { return m_Positions; }
    virtual float *GetColors() const { return m_Colors; }
    virtual float *GetUVs() const { return m_Uvs; }
    virtual float *GetNormals() const { return m_Normals; }
    virtual unsigned short *GetIndices() const {return m_Indices; }
    virtual int GetVerticesCount() const {return m_VerticesCount;}
    virtual int GetIndicesCount() const {return m_IndicesCount;}

    virtual void SetIndices(const unsigned short *indices, int size);
    virtual void SetPositions(float positions[][3], int size);
    virtual void SetUVs(float uvs[][2], int size);
    virtual void SetColors(float uvs[][4], int size);
    virtual void SetNormals(float normals[][3], int size);
    
private:
    void LoadFromFile(const char *fileName);
protected:
    std::string m_FileName;
    int m_VerticesCount;
    int m_IndicesCount;
    float *m_Positions;
    float *m_Colors;
    float *m_Uvs;
    float *m_Normals;
    unsigned short *m_Indices;
};
} // namespace magic

#endif /* CMesh_h */
