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
        it->second->SetData(data, size);
    }
    else
    {
        m_PropertyValue[propertyName] = new SPropertyData(data, size);
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

const char *CMaterial::GetAttributeName(int index) const
{
    if (index >=0 && index < m_VertexAttribute.size())
    {
        return m_VertexAttribute[index].name.c_str();
    }
    return "";
}

void CMaterial::AddAttribute(const char *name)
{
    SVertexAttribute attribute = {name};
    m_VertexAttribute.push_back(attribute);
}

}
