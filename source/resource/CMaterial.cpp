#include "resource/CMaterial.h"

#include <string.h>

namespace magic
{
CMaterial::CMaterial()
{
    memset(m_Shaders, 0, sizeof(IShader *) * EShaderType::Count);
}
CMaterial::~CMaterial()
{
    for (auto it = m_PropertyValue.begin(); it != m_PropertyValue.end(); ++it)
    {
        delete it->second;
    }
    m_PropertyValue.clear();
}

void CMaterial::SetShader(EShaderType type, IShader *shader)
{
    m_Shaders[type] = shader;
}

IShader *CMaterial::GetShader(EShaderType type) const
{
    return m_Shaders[type];
}

void CMaterial::SetProperty(const char *propertyName, void *data, int size)
{
    auto it = m_PropertyValue.find(propertyName);
    if (it != m_PropertyValue.end())
    {
        it->second->SetData(propertyName, data, size);
    }
    else
    {
        m_PropertyValue[propertyName] = new SPropertyData(propertyName, data, size);
    }
}

void *CMaterial::GetPropertyValue(const char *propertyName, int &size) 
{
    auto it = m_PropertyValue.find(propertyName);
    if (it != m_PropertyValue.end())
    {
        size = it->second->dataSize;
        return it->second->pData;
    }
    size = 0;
    return nullptr;
}

IMaterialProperty *CMaterial::GetFirstProperty()
{
    if (m_PropertyValue.size() > 0)
    {
        m_PropertyIterator = m_PropertyValue.begin();
        return m_PropertyIterator->second;
    }
    return nullptr;
}

IMaterialProperty *CMaterial::GetNextProperty()
{
    if (++m_PropertyIterator != m_PropertyValue.end())
    {
        return m_PropertyIterator->second;
    }
    return nullptr;
}
}
