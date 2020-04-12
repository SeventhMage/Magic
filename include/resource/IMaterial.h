#ifndef _MAGIC_I_MATERIAL_H_
#define _MAGIC_I_MATERIAL_H_

#include "IResource.h"
#include "IShader.h"

namespace magic
{
class IMaterial : public IResource
{
public:
    virtual ~IMaterial(){}
    virtual EResourceType GetType() const { return EResourceType::Material; }
    virtual void SetShader(EShaderType, IShader *) = 0;
    virtual IShader *GetShader(EShaderType) const = 0;
    virtual void SetProperty(const char *propertyName, void *data, int size) =0;
    virtual void *GetPropertyValue(const char *propertyName, int &size) = 0;
    /**
     * Vertex attribute
     * **/
    virtual int GetAttributeCount() const = 0;
    virtual const char *GetAttributeName(int index) const = 0;
    virtual void AddAttribute(const char *name) = 0;
};
} // namespace magic

#endif