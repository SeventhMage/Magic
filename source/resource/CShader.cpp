#include "resource/CShader.h"

#include <string.h>

namespace magic
{
CShader::CShader(EShaderType type, const char *source)
:m_ShaderType(type)
{
    int len = strlen(source);
    m_Source = new char[len];
    memcpy(m_Source, source, len * sizeof(char));
}

CShader::~CShader()
{
    if (m_Source)
        delete[]m_Source;
}


} // namespace magic