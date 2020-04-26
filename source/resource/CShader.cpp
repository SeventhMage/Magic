#include "resource/CShader.h"
#include "base/magicType.h"
#include "base/Log.h"

#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
    
namespace magic
{
CShader::CShader(EShaderType type, const char *source, int size)
    : m_ShaderType(type)
{
    m_Source = (char *)malloc(size);
    memcpy(m_Source, source, size);
}

CShader::CShader(EShaderType type, const char *fileName)
:m_ShaderType(type)
{
    struct stat tagStat;
    int ret = stat(fileName, &tagStat);
    if (ret == 0)
    {
        FILE *pFile = fopen(fileName, "rb");
        if (pFile)
        {
            long long size = tagStat.st_size + 1;
            m_Source = (char *)malloc(size);
            fread(m_Source, size, 1, pFile);
            m_Source[size - 1] = 0;
            fclose(pFile);
        }
        else
        {
            LogError("CShader::CShader() Open file %s failed", fileName);
        }
    }
    else
    {
        LogError("CShader::CShader() stat failed:%s", fileName);
    }
}

CShader::~CShader()
{
    if (m_Source)
        free(m_Source);
}

} // namespace magic
