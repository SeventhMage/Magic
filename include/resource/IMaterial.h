#ifndef _MAGIC_I_MATERIAL_H_
#define _MAGIC_I_MATERIAL_H_

#include "IResource.h"
#include "IShader.h"

namespace magic
{
class IMaterialProperty
{
public:
    virtual ~IMaterialProperty() {}
    virtual const char *GetName() const = 0;
    virtual int GetSize() const = 0;
    virtual void *GetData() const = 0;
};

class IMaterial : public IResource
{
public:
    virtual ~IMaterial(){}
    virtual EResourceType GetType() const { return EResourceType::Material; }
    virtual void SetShader(EShaderType type, const char *shaderName) = 0;
    virtual void SetShader(EShaderType type, const char *shaderSource, int size) = 0;
    virtual IShader *GetShader(EShaderType) const = 0;
    virtual void SetProperty(const char *propertyName, void *data, int size) = 0;
    virtual void *GetPropertyValue(const char *propertyName, int &size) = 0;
    virtual IMaterialProperty *GetFirstProperty() = 0;
    virtual IMaterialProperty *GetNextProperty() = 0;
};
} // namespace magic

#endif
