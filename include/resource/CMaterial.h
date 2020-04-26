#ifndef _MAGIC_C_MATERIAL_H_
#define _MAGIC_C_MATERIAL_H_

#include "IMaterial.h"

#include <map>
#include <vector>
#include <string>
#include <string.h>

namespace magic
{
struct SPropertyData : public IMaterialProperty
{
    SPropertyData(const char *name, void *data, int size)
    {
        pData = malloc(size);
        memcpy(pData, data, size);
        dataSize = size;
        propertyName = name;
    }
    ~SPropertyData()
    {
        free(pData);
    }

    virtual const char *GetName() const { return propertyName.c_str(); }
    virtual int GetSize() const { return dataSize; }
    virtual void *GetData() const { return pData; }
    
    void SetData(const char *name, void *data, int size)
    {
        if (dataSize != size)
        {
            free(pData);
            pData = malloc(size);
        }
        memcpy(pData, data, size);
        propertyName = name;
    }
    std::string propertyName;
    void *pData;
    int dataSize;
};

class CMaterial : public IMaterial
{
public:
    CMaterial();
    virtual ~CMaterial();
    virtual void SetShader(EShaderType type, IShader *shader);
    virtual IShader *GetShader(EShaderType) const;
    virtual void SetProperty(const char *propertyName, void *data, int size);
    virtual void *GetPropertyValue(const char *propertyName, int &size);
    virtual IMaterialProperty *GetFirstProperty();
    virtual IMaterialProperty *GetNextProperty();
private:
    IShader *m_Shaders[EShaderType::Count];
    std::map<std::string, SPropertyData *> m_PropertyValue;
    std::map<std::string, SPropertyData *>::iterator m_PropertyIterator;
};
}


#endif /* CMaterial_h */
