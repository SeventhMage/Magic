#ifndef _MAGIC_I_SHADER_H_
#define _MAGIC_I_SHADER_H_
#include "IResource.h"
namespace magic
{
enum EShaderType
{
    Vertex = 0,
    Fragment,
    Compute,
    
    Count,
};
class IShader : public IResource
{
public:
    virtual EResourceType GetType() const { return EResourceType::Shader; }
    virtual EShaderType GetShaderType() const = 0;
    virtual char *GetSource() const = 0;
};
}

#endif