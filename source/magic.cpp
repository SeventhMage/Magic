#include "../include/magic.h"
#include "CMagic.h"

namespace magic
{
IMagic *GetMagic()
{
    return CMagic::Instance();
}

void Clean()
{
    CMagic::DeleteInstance();
}
}