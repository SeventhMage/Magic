#include "CTime.h"

#include <time.h>
#include <sys/time.h>

namespace magic
{
CTime::CTime()
:m_DeltaTime(0)
{
    
}

ulong CTime::GetRunTime() const
{
    return clock() * 1000 / CLOCKS_PER_SEC;
}

ulong CTime::GetSystemTime() const
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec * 0.001;
}

void CTime::SetDeltaTime(ulong time)
{
    m_DeltaTime = time;
    //m_RunTime += time;
}
}
