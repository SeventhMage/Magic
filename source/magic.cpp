#include "magic.h"
#include "CMagic.h"

namespace magic
{
static IMagic *s_magic = nullptr;
IMagic *CreateMagic(void *context, const char *title, int width, int height, unsigned int flags)
{
    s_magic = new CMagic(context, title, width, height, flags);
    return s_magic;
}

void Clean()
{
    if (s_magic)
        delete s_magic;
}
}
