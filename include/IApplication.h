#ifndef _MAGIC_I_APPLICATION_H_
#define _MAGIC_I_APPLICATION_H_

namespace magic
{
class IApplication
{
public:
    virtual ~IApplication(){}
    virtual bool Run() = 0;
    virtual long GetSystemTime() = 0;
};
} // namespace magic

#endif