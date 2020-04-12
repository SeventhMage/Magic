#ifndef _MAGIC_I_SHADER_PROGRAM_H_
#define _MAGIC_I_SHADER_PROGRAM_H_

#include "resource/IShader.h"
#include "base/magicType.h"

namespace magic
{
enum E_STAND_SHADER
{
    ESS_SHADER_IDENTITY = 0,
    ESS_SHADER_FLAT,
    ESS_SHADER_SHADED,
    ESS_SHADER_DEFAULT_LIGHT,
    ESS_SHADER_POINT_LIGHT_DIFF,
    ESS_SHADER_TEXTURE_REPLACE,
    ESS_SHADER_TEXTURE_MODULATE,
    ESS_SHADER_TEXTURE_POINT_LIGHT_DIFF,
    ESS_SHADER_TEXTURE_RECT_REPLACE,
    ESS_SHADER_LAST
};

class IShaderProgram
{
public:
    virtual ~IShaderProgram() {}
    virtual void Bind() = 0;
    virtual void SetUniform(const char *name, void *value) = 0;
    virtual void CreateStandShader(E_STAND_SHADER standShader) = 0;
    virtual bool Attach(IShader *shader) = 0;
    virtual bool AttachSource(const char *shaderSrc, EShaderType shaderType) = 0;
    virtual void Detach(EShaderType shaderType) = 0;
    virtual bool Link() = 0;
    virtual uint GetHandle() const = 0;
    virtual void BindAttributeLocation(int argc, ...) = 0;
    virtual void BindAttributeLocation(int index, const char *name) = 0;


};


} // namespace magic

#endif