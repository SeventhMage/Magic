#ifndef _MAGIC_C_SHADER_H_
#define _MAGIC_C_SHADER_H_

#include "IShader.h"

namespace magic
{
class CShader : public IShader
{
public:
    CShader(EShaderType type, const char *source, int size);
    CShader(EShaderType type, const char *fileName);
    virtual ~CShader();

    virtual EShaderType GetShaderType() const { return m_ShaderType; }
    virtual char *GetSource() const { return m_Source; }
private:
    EShaderType m_ShaderType;
    char *m_Source;
};
} // namespace magic

#endif /* CShader_h */
