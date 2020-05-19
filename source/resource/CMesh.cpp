#include "resource/CMesh.h"
#include "base/magicDef.h"
#include "base/Log.h"
#include "rapidxml.hpp"

#include <fstream>
#include <functional>
#include <sys/stat.h>

namespace magic
{
CMesh::CMesh(const char *fileName)
:m_FileName(fileName)
,m_VerticesCount(0)
,m_IndicesCount(0)
,m_Positions(nullptr)
,m_Colors(nullptr)
,m_Uvs(nullptr)
,m_Normals(nullptr)
,m_Indices(nullptr)
{
    if (strcmp(fileName, "") != 0)
    {
        LoadFromFile(fileName);
    }
}

CMesh::~CMesh()
{
    SAFE_DEL_ARRAY(m_Indices);
    SAFE_DEL_ARRAY(m_Positions);
    SAFE_DEL_ARRAY(m_Colors);
    SAFE_DEL_ARRAY(m_Uvs);
}

void CMesh::SetIndices(const unsigned short *indices, int size)
{
    SAFE_DEL_ARRAY(m_Indices);
    m_Indices = new unsigned short[size / sizeof(unsigned short)];
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

void CMesh::SetNormals(float (*normals)[3], int size)
{
    SAFE_DEL_ARRAY(m_Normals);
    m_Normals = new float[size / sizeof(float)];
    memcpy(m_Normals, normals, size);
}

template<typename T>
void parseValue(char *textValue, std::function<void(T *, int)> fcall)
{
    StringArray valueArray = Split(textValue, " ");
    T *result = new T[valueArray.size()];
    for (size_t i=0; i<valueArray.size(); ++i)
    {
        result[i] = atof(valueArray[i].c_str());
    }
    fcall(result, (int)valueArray.size() * sizeof(T));
    delete[]result;
};

void CMesh::LoadFromFile(const char *fileName)
{
    /*
    std::ifstream infile(fileName, std::ios::in);
    if (!infile.is_open())
    {
        LogError("Load Mesh failed:%s\n", fileName);
        return;
    }
    infile.seekg(0, std::ios::end);
    long long length = infile.tellg();
    infile.seekg(0, std::ios::beg);
    char *buf = new char[length + 1];
    infile.read(buf, sizeof(char) * length);
    buf[length] = 0;
    rapidxml::xml_document<> doc;
    doc.parse<0>(buf);
    infile.close();
    */

    rapidxml::xml_document<> doc;
    char *buf = nullptr;
    struct stat tagStat;
    int ret = stat(fileName, &tagStat);
    if (ret == 0)
    {
        FILE *pFile = fopen(fileName, "rb");
        if (pFile)
        {
            long long size = tagStat.st_size + 1;
            buf = (char *)malloc(size);
            fread(buf, size, 1, pFile);
            buf[size - 1] = 0;
            doc.parse<0>(buf);
            fclose(pFile);
        }
        else
        {
            LogError("CMesh::LoadFromFile Open file %s failed", fileName);
            return;
        }
    }
    else
    {
        LogError("CMesh::LoadFromFile stat failed:%s", fileName);
        return;
    }

    rapidxml::xml_node<> *rootNode = doc.first_node("Mesh");
    if (rootNode)
    {
        rapidxml::xml_node<> * posnode = rootNode->first_node("Position");
        if (posnode)
            parseValue<float>(posnode->value(),[this](float *value, int size){ SetPositions((float (*)[3]) value, size); });
        
        rapidxml::xml_node<> * colornode = rootNode->first_node("Color");
        if (colornode)
            parseValue<float>(colornode->value(),[this](float *value, int size){ SetColors((float (*)[4]) value, size); });
        
        rapidxml::xml_node<> * normalnode = rootNode->first_node("Normal");
        if (normalnode)
            parseValue<float>(normalnode->value(),[this](float *value, int size){ SetNormals((float (*)[3]) value, size); });
        
        rapidxml::xml_node<> * uvnode = rootNode->first_node("UV");
        if (uvnode)
            parseValue<float>(uvnode->value(),[this](float *value, int size){ SetUVs((float (*)[2]) value, size); });
        
        rapidxml::xml_node<> * indexnode = rootNode->first_node("Index");
        if (indexnode)
            parseValue<unsigned short>(indexnode->value(),[this](unsigned short *value, int size){ SetIndices(value, size); });
    }
    delete[]buf;
}

}
