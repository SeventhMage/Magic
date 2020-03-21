#include "CObject.h"

namespace magic
{
CObject::CObject()
{
    static OID s_IDCount = 0;
    m_ID = ++s_IDCount;
}

}