#ifndef _MAGIC_C_TIME_H_
#define _MAGIC_C_TIME_H_

#include "ITime.h"

namespace magic
{
class CTime : public ITime
{
public:
    CTime();
    virtual ulong GetDeltaTime() const { return m_DeltaTime; }
    virtual ulong GetRunTime() const;
    virtual ulong GetSystemTime() const;
    
    void SetDeltaTime(ulong time);
private:
    ulong m_DeltaTime;
    //ulong m_RunTime;
};
}

#endif


