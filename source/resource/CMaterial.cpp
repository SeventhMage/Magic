#include "resource/CMaterial.h"
#include "resource/CShader.h"
#include "base/magicDef.h"
#include "base/Log.h"
#include "rapidxml.hpp"

#include <string.h>
#include <sys/stat.h>
#include <fstream>

namespace magic
{
CMaterial::CMaterial(IResourceManager *pResourceMgr, const char *fileName)
: m_ResourceMgr(pResourceMgr)
, m_FileName(fileName)
{
    memset(m_Shaders, 0, sizeof(IShader *) * EShaderType::Count);
    if (strcmp(fileName, ""))
    {
        LoadFromFile(fileName);
    }
}

CMaterial::~CMaterial()
{
    for (auto it = m_PropertyValue.begin(); it != m_PropertyValue.end(); ++it)
    {
        delete it->second;
    }
    m_PropertyValue.clear();
    for (int i=0; i<EShaderType::Count; ++i)
    {
        SAFE_DEL(m_Shaders[i]);
    }
}

void CMaterial::SetShader(EShaderType type, const char *shaderName)
{
    m_Shaders[type] = (IShader *)m_ResourceMgr->LoadResource(shaderName, EResourceType::Shader);
}

void CMaterial::SetShader(EShaderType type, const char *shaderSource, int size)
{
    m_Shaders[type] = new CShader(type, shaderSource, size);
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

IImage *CMaterial::GetImage(int index) const
{
    if (index >=0 && index < m_ImageVec.size())
    {
        return m_ImageVec[index];
    }
    return nullptr;
}

void CMaterial::LoadFromFile(const char *fileName)
{
    /*
    std::ifstream infile(fileName, std::ios::in);
    if (!infile)
    {
        LogError("Load Material failed %s\n", fileName);
        return;
    }
    infile.seekg(0, std::ios::end);
    int length = (int)infile.tellg() + 1;
    infile.seekg(0, std::ios::beg);
    char *buf = new char[length];
    memset(buf, 0, sizeof(char) * (length));
    infile.read(buf, sizeof(char) * length);
    buf[length - 1] = 0;
    infile.close();

    rapidxml::xml_document<> doc;
    doc.parse<0>(buf);
    */

    rapidxml::xml_document<> doc;
    char *buf = nullptr;
    struct stat tagStat;
    int ret = stat(fileName, &tagStat);
    if (ret == 0)
    {
        FILE *pFile = fopen(fileName, "rb");
        if (pFile)
        {
            long long size = tagStat.st_size + 1;
            buf = (char *)malloc(size);
            fread(buf, size, 1, pFile);
            buf[size - 1] = 0;
            doc.parse<0>(buf);
            fclose(pFile);
        }
        else
        {
            LogError("CMaterial::LoadFromFile Open file %s failed", fileName);
            return;
        }
    }
    else
    {
        LogError("CMaterial::LoadFromFile stat failed:%s", fileName);
        return;
    }




    rapidxml::xml_node<> *rootNode = doc.first_node("Material");
    if (rootNode)
    {
        rapidxml::xml_node<> * shadernode = rootNode->first_node("Shader");
        if (shadernode)
        {
            const char *vertShader = shadernode->first_attribute("vert")->value();
            const char *fragShader = shadernode->first_attribute("frag")->value();
            SetShader(EShaderType::Vertex, vertShader);
            SetShader(EShaderType::Fragment, fragShader);
        }
        
        int textureUnit = 0;
        for (rapidxml::xml_node<> * texturenode = rootNode->first_node("Texture"); texturenode; texturenode = texturenode->next_sibling())
        {
            const char *path  = texturenode->first_attribute("path")->value();
            m_ImageVec.push_back((IImage *)m_ResourceMgr->LoadResource(path, EResourceType::Image));
            const char *property  = texturenode->first_attribute("property")->value();
            SetProperty(property, &textureUnit, sizeof(textureUnit));
            ++textureUnit;
        }
    }
    delete[]buf;
}

}
