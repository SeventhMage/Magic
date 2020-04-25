#include "CResourceManager.h"
#include "base/StringHelper.h"
#include "CTGAImage.h"

#include "FileWrapper.h"

namespace magic
{

IResource *CResourceManager::LoadResource(const char *fileName, EResourceType type)
{
    switch (type)
    {
    case EResourceType::Image:
        return LoadImage(fileName);
    default:
        break;
    }
    return nullptr;
}

IResource *CResourceManager::LoadImage(const char *fileName)
{
    std::string extName = GetFileExtName(fileName);
    if (extName == "tga")
    {
        CTGAImage *pImage = new CTGAImage();
#ifdef __APPLE__
        fileName = GetBundleFileName(fileName);
#endif
        pImage->Load(fileName);
        return pImage;
    }
    return nullptr;
}

}
