#ifndef _MAGIC_COMMON_BASE_SCOLOR_H_
#define _MAGIC_COMMON_BASE_SCOLOR_H_

#include "magicType.h"

namespace magic
{
typedef struct SColor
{
	SColor() : color(((255 & 0xff) << 24) | ((255 & 0xff) << 16) | ((255 & 0xff) << 8) | ((255 & 0xff))) {}
	SColor(uint a, uint r, uint g, uint b)
		: color(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | ((b & 0xff))) {}
	SColor(uint clr) : color(clr) {}
	uint GetAlpha() { return color >> 24; }
	uint GetRed() { return (color >> 16) & 0xff; }
	uint GetGreen() { return (color >> 8) & 0xff; }
	uint GetBlue() { return color & 0xff; }
	void SetAlpha(uint a) { color = ((a & 0xff) << 24) | (color & 0x00ffffff); }
	void SetRed(uint r) { color = ((r & 0xff) << 16) | (color & 0xff00ffff); }
	void SetGreen(uint g) { color = ((g & 0xff) << 8) | (color & 0xffff00ff); }
	void SetBlue(uint b) { color = (b & 0xff) | (color & 0xffffff00); }
	uint color;
} Color;
} // namespace magic

#endif