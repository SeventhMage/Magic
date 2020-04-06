#include "magic.h"
#include "CMagic.h"

namespace magic
{
static IMagic *s_magic = nullptr;
IMagic *CreateMagic(SRenderContent *context, const char *title, int width, int height)
{
    s_magic = new CMagic(context, title, width, height);
    return s_magic;
}

void Clean()
{
    if (s_magic)
        delete s_magic;
}
}
