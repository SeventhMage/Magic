#ifndef _MAGIC_C_OBJ_LOADER_H_
#define _MAGIC_C_OBJ_LOADER_H_

#include "CResourceLoader.h"
#include "resource/IMesh.h"
#include "resource/IMaterial.h"

namespace magic
{
class CObjLoader : public CResourceLoader
{
public:
    CObjLoader(){}
    ~CObjLoader(){}
    bool Load(const char *fileName, IMesh *pMesh, IMaterial *pMaterial);
    struct SFace
    {
        SFace()
        {
            for (int i=0; i<4; ++i)
            {
                positionIndex[i] = -1;
                uvIndex[i] = -1;
                normalIndex[i] = -1;
            }
        }
        short positionIndex[4];
        short uvIndex[4];
        short normalIndex[4];
        short indexCount;
    };
private:
    bool ReadLine(std::ifstream &in, char *out, int size);
};
}

#endif
