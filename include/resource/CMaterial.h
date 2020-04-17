#ifndef _MAGIC_C_MATERIAL_H_
#define _MAGIC_C_MATERIAL_H_

#include "IMaterial.h"

#include <map>
#include <vector>
#include <string>
#include <string.h>

namespace magic
{
class CMaterial : public IMaterial
{
public:
    struct SPropertyData
    {
        SPropertyData(void *data, int size)
        {
            pData = malloc(size); 
            memcpy(pData, data, size);
            dataSize = size;
        }
        ~SPropertyData()
        {
            free(pData);
        }

        void SetData(void *data, int size)
        {
            if (dataSize != size)
            { 
                free(pData);
                pData = malloc(size);
            }
            memcpy(pData, data, size);
        }

        void *pData;
        int dataSize;
    };

    struct SVertexAttribute
    {
        std::string name;
    };

    CMaterial();
    virtual ~CMaterial();
    virtual void SetShader(EShaderType type, IShader *shader);
    virtual IShader *GetShader(EShaderType) const;
    virtual void SetProperty(const char *propertyName, void *data, int size);
    virtual void *GetPropertyValue(const char *propertyName, int &size);
    virtual int GetAttributeCount() const { return m_VertexAttribute.size(); }
    virtual const char *GetAttributeName(int index) const;
    virtual void AddAttribute(const char *name);
private:
    IShader *m_Shaders[EShaderType::Count];
    std::map<std::string, SPropertyData *> m_PropertyValue;
    std::vector<SVertexAttribute> m_VertexAttribute;
};
}


#endif /* CMaterial_h */
