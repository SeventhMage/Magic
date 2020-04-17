#include "resource/CShader.h"

#include <string.h>
#include <stdlib.h>

namespace magic
{
CShader::CShader(EShaderType type, const char *source, int size)
:m_ShaderType(type)
{
    m_Source = (char *)malloc(size);
    memcpy(m_Source, source, size);
}

CShader::~CShader()
{
    free(m_Source);
}


} // namespace magic
