#include "CObjLoader.h"
#include "base/StringHelper.h"
#include "math/CVector3.h"
#include "math/CVector2.h"
#include "base/Log.h"
#include <fstream>
#include <vector>

namespace magic
{
bool CObjLoader::Load(const char *fileName, IMesh *pMesh, IMaterial *pMaterial)
{
    std::ifstream in(fileName, std::ios::in);
    std::vector<CVector3> positionList;
    std::vector<CVector3> normalList;
    std::vector<CVector2> uvList;
    std::vector<CVector3> positionListForMesh;
    std::vector<CVector3> normalListForMesh;
    std::vector<CVector2> uvListForMesh;
    std::vector<unsigned short> indexList;
    std::vector<SFace> faceList;
    if (in.is_open())
    {
        in.seekg(0, std::ios::end);
        long long length = in.tellg();
        in.seekg(0, std::ios::beg);
        
        bool bHaveTexCoord = false;
        char *buf = new char[length];
        while (ReadLine(in, buf, (int)length * sizeof(char)))
        {
            if ('v' == buf[0] && ' ' == buf[1]) //顶点位置
            {
                CVector3 v;
                char temp[8];
                if (sscanf(buf, "%s %f %f %f", temp, &v.x, &v.y, &v.z) != -1)
                {
                    positionList.push_back(v);
                }
            }
            else if ('v' == buf[0] && 'n' == buf[1]) //法线
            {
                CVector3 v;
                char temp[8];
                if (sscanf(buf, "%s %f %f %f", temp, &v.x, &v.y, &v.z) != -1)
                {
                    normalList.push_back(v);
                }
            }
            else if ('v' == buf[0] && 't' == buf[1]) //纹理坐标
            {
                bHaveTexCoord = true;
                CVector2 v;
                char temp[8];
                if (sscanf(buf, "%s %f %f", temp, &v.x, &v.y) != -1)
                {
                    uvList.push_back(v);
                }
            }
            else if ('f' == buf[0]) //面
            {
                SFace face;
                
                StringArray split = Split(buf, " ");
                //下标0为'f'
                face.indexCount = split.size() - 1;
                const char *format = "";
                if (bHaveTexCoord)
                    format = "%hd/%hd/%hd";
                else
                    format = "%hd//%hd";
                for (int i = 0, j=1; j < split.size(); ++i, ++j)
                {
                    if (bHaveTexCoord)
                    {
                        if (sscanf(split[j].c_str(), format, &face.positionIndex[i], &face.uvIndex[i], &face.normalIndex[i]) == -1)
                            continue;
                        --face.positionIndex[i];
                        --face.uvIndex[i];
                        --face.normalIndex[i];
                    }
                    else
                    {
                        if (sscanf(split[j].c_str(), format, &face.positionIndex[i], &face.normalIndex[i]) == -1)
                            continue;
                        --face.positionIndex[i];
                        --face.normalIndex[i];
                    }
                }
                
                faceList.push_back(face);
            }
        }
        delete[]buf;
        in.close();
        
        // parse mesh data
        for (size_t i = 0; i<faceList.size(); ++i)
        {
            if (faceList[i].indexCount == 3)
            {
                for (size_t j = 0; j < faceList[i].indexCount; ++j)
                {
                    positionListForMesh.push_back(positionList[faceList[i].positionIndex[j]]);
                    if (bHaveTexCoord)
                        uvListForMesh.push_back(uvList[faceList[i].uvIndex[j]]);
                    normalListForMesh.push_back(normalList[faceList[i].normalIndex[j]]);
                    indexList.push_back(faceList[i].positionIndex[j]);
                }
            }
            else if (faceList[i].indexCount == 4)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    positionListForMesh.push_back(positionList[faceList[i].positionIndex[j]]);
                    if (bHaveTexCoord)
                        uvListForMesh.push_back(uvList[faceList[i].uvIndex[j]]);
                    normalListForMesh.push_back(normalList[faceList[i].normalIndex[j]]);
                    indexList.push_back(faceList[i].positionIndex[j]);
                }
                
                for (int j=0; j<3; ++j)
                {
                    int index2 = j;
                    if (j > 0)
                        index2 = j + 1;
                    positionListForMesh.push_back(positionList[faceList[i].positionIndex[index2]]);
                    if (bHaveTexCoord)
                        uvListForMesh.push_back(uvList[faceList[i].uvIndex[index2]]);
                    normalListForMesh.push_back(normalList[faceList[i].normalIndex[index2]]);
                    indexList.push_back(faceList[i].positionIndex[index2]);
                }
                
            }
        }
        pMesh->SetPositions((float (*)[3])&positionListForMesh[0], sizeof(CVector3) * positionListForMesh.size());
        pMesh->SetNormals((float (*)[3])&normalListForMesh[0], sizeof(CVector3) * normalListForMesh.size());
        if (bHaveTexCoord)
            pMesh->SetUVs((float (*)[2])&uvListForMesh, sizeof(CVector2) * uvListForMesh.size());
        //pMesh->SetIndices(&indexList[0], sizeof(unsigned short) * indexList.size());
    }
    else
    {
        LogError("Can't open resource:%s\n", fileName);
        return false;
    }
    return true;
}

bool CObjLoader::ReadLine(std::ifstream &in, char *out, int size)
{
    while (!in.eof())
    {
        in.getline(out, size);

        int i = 0;
        for (; i < size; ++i)
        {
            if (out[i] == 0)
                break;
            if (isspace(out[i]))
                continue;
            if (out[i] == '#')
                break;
            break;
        }
        if (isspace(out[i]) || out[i] == '#' || out[i] == 0)
            continue;
        return true;
    }
    return false;
}
}
