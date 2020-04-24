#include "CTime.h"

#include <time.h>

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
    return time(0);
}

void CTime::SetDeltaTime(ulong time)
{
    m_DeltaTime = time;
    //m_RunTime += time;
}
}
