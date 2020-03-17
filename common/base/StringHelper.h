#ifndef _MAGIC_COMMON_BASE_STRING_HELPER_H_
#define _MAGIC_COMMON_BASE_STRING_HELPER_H_

#include "magicType.h"

namespace magic
{
std::string GetFileExtName(const char *filename);

StringArray Split(const std::string &str, const std::string &delims);

std::string Replace(const std::string &str, const std::string &src, const std::string &dst);
} // namespace magic

#endif