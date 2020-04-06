#include "CShaderProgram.h"

namespace magic
{
CShaderProgram::CShaderProgram()
{
}

CShaderProgram::~CShaderProgram()
{
}

void CShaderProgram::SetUniform(const char *name, void *value)
{
    int location = GetUniformLocation(name);
    if (location >= 0)
    {
        SetUniform(location, value);
    }
}

void CShaderProgram::SetUniform(int location, void *value)
{
    if (m_uniforms.find(location) != m_uniforms.end())
        m_uniforms[location].SetValue(value);
}

int CShaderProgram::GetUniformLocation(const char *name) const
{
    UniformArray::const_iterator cit = m_uniforms.begin();
    for (; cit != m_uniforms.end(); ++cit)
    {
        if (0 == strcmp(cit->second.m_name, name))
        {
            return cit->second.m_location;
        }
    }
    return -1;
}

int CShaderProgram::GetUniformTypeSizeByLocation(int location) const
{
    auto it = m_uniforms.find(location);
    if (it != m_uniforms.end())
    {
        return it->second.m_size;
    }
    return -1;
}

} // namespace magic
}
