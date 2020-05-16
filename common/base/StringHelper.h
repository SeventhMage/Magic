#ifndef _MAGIC_COMMON_BASE_STRING_HELPER_H_
#define _MAGIC_COMMON_BASE_STRING_HELPER_H_

#include "magicType.h"

#include <string.h>

namespace magic
{
static std::string GetFileExtName(const char *filename)
{
    const char *pLastPoint = strrchr(filename, '.');
    if (pLastPoint)
    {
        return std::string(pLastPoint + 1);
    }
    return "";
}

static std::string GetFileName(const char *fullPath)
{
    const char *pLastSlash = strrchr(fullPath, '/');
    if (pLastSlash)
    {
        return std::string(pLastSlash + 1);
    }
    return fullPath;
}

static StringArray Split(const std::string &str, const std::string &delims)
{
    StringArray strRet;
    size_t start = 0, pos = 0;
    do
    {
        pos = str.find_first_of(delims, start);
        if (pos == start)
        {
            start = pos + 1;
        }
        else if (pos == std::string::npos)
        {
            strRet.push_back(str.substr(start));
            break;
        }
        else
        {
            strRet.push_back(str.substr(start, pos - start));
            start = pos + 1;
        }

        start = str.find_first_not_of(delims, start);

    } while (pos != std::string::npos);

    return strRet;
}



static std::string Replace(const std::string &str, const std::string &src, const std::string &dst)
{
    if (src == dst)
        return str;
    std::string out = str;
    size_t pos = str.find(src, 0);
    while (pos != std::string::npos)
    {
        out.replace(pos, src.size(), dst);
        pos = out.find(src, pos + dst.size());
    }
    return out;
}
} // namespace magic

#endif
