#ifndef _MAGIC_C_GLES3_SHADERPROGRAM_H_
#define _MAGIC_C_GLES3_SHADERPROGRAM_H_

#include "../CShaderProgram.h"
#include "gl3.h"

namespace magic
{
class CGLES3ShaderProgram : public CShaderProgram
{
public:
    CGLES3ShaderProgram();
    virtual ~CGLES3ShaderProgram();
    virtual void CreateStandShader(E_STAND_SHADER standShader);
    virtual bool Attach(IShader *shader);
    virtual bool AttachSource(const char *shaderSrc, EShaderType shaderType);
    virtual void Detach(EShaderType shaderType);
    virtual bool Link();
    virtual uint GetHandle() const { return m_hProgram; }

    virtual void Bind();
    virtual void BindAttributeLocation(int argc, ...);
    virtual void BindAttributeLocation(int index, const char *name);

private:
    void GetShaderUniform();

private:
    GLuint m_hProgram;
    GLuint m_hShaders[EShaderType::Count];
};
} // namespace magic

#endif