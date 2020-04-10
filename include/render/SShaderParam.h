#ifndef _MAGIC_S_SHADER_PARAM
#define _MAGIC_S_SHADER_PARAM

#include <stdlib.h>

namespace magic
{
struct SShaderParam
{
    enum EParamType
    {
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        MAT3,
        MAT4,
    };
    SShaderParam(const char *name, void *data, int size)
    {
        strncpy(paramName, name, MAX_PATH * sizeof(char));
        paramData = malloc(size);
        memcpy(paramData, data, size);
        paramSize = size;
    }

    SShaderParam(const SShaderParam &param)
    {
        strncpy(paramName, param.paramName, MAX_PATH * sizeof(char));
        paramSize = param.paramSize;
        paramData = malloc(paramSize);
        memcpy(paramData, param.paramData, paramSize);
    }

    SShaderParam &operator=(const SShaderParam &param)
    {
        if (this != &param)
        {
            if (param.paramSize != paramSize)
            {
                paramData = realloc(paramData, paramSize);
                paramSize = param.paramSize;
            }
            memcpy(paramData, param.paramData, paramSize);
            strncpy(paramName, param.paramName, MAX_PATH * sizeof(char));
        }
        return *this;
    }

    ~SShaderParam()
    {
        if (paramData)
            free(paramData);
    }
    static const int MAX_PATH = 256;
    char paramName[MAX_PATH];
    void *paramData;
    int paramSize;
    int paramType;
};

}

#endif