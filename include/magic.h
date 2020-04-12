#ifndef _MAGIC_H_
#define _MAGIC_H_

#include "IMagic.h"
#include "render/SRenderContext.h"

namespace magic
{
IMagic *CreateMagic(SRenderContext *context, const char *title, int width, int height);
void Clean();
}

#endif
