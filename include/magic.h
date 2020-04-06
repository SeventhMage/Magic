#ifndef _MAGIC_H_
#define _MAGIC_H_

#include "IMagic.h"
#include "render/SRenderContent.h"

namespace magic
{
IMagic *CreateMagic(SRenderContent *context, const char *title, int width, int height);
void Clean();
}

#endif
