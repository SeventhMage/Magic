#ifndef _MAGIC_I_TIME_H_
#define _MAGIC_I_TIME_H_

#include "base/magicType.h"

namespace magic
{
class ITime
{
public:
    virtual ~ITime(){}
    virtual ulong GetDeltaTime() const = 0;
    virtual ulong GetRunTime() const = 0;
    virtual ulong GetSystemTime() const = 0;
};
}

#endif
