#include "../include/magic.h"
#include "CMagic.h"

namespace magic
{
static IMagic *GetMagic()
{
    return CMagic::Instance();
}

static void Clean()
{
    CMagic::DeleteInstance();
}
}