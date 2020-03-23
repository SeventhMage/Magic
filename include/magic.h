#ifndef _MAGIC_H_
#define _MAGIC_H_

#include "IMagic.h"

namespace magic
{
IMagic *CreateMagic(void *context, const char *title, int width, int height, unsigned int flags);
void Clean();
}

#endif
