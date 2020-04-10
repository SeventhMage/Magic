#ifndef _MAGIC_RENDER_ITEXTURE_H_
#define _MAGIC_RENDER_ITEXTURE_H_

#include "base/magicType.h"

namespace magic
{
enum EColorFormat
{
	ALPHA,
	RGB,
	RGBA,
	RGB16F,
	RGBA16F,
	BGR,
	BGRA,
	LUMINANCE,
};

enum EPixelType
{
	UNSIGNED_BYTE,
	UNSIGNED_SHORT_5_6_5,
	UNSIGNED_SHORT_4_4_4_4,
	UNSIGNED_SHORT_5_5_5_1,
};

class ITexture
{
public:
    virtual ~ITexture(){}
    virtual void Bind(uint slot = 0) = 0;
	virtual void UnBind() = 0;
	virtual void Create2D(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data) = 0;
	virtual void CreateCube(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data[6]) = 0;
	virtual void CreateDepth(int width, int height) = 0;
	virtual void Create(uint target, uint handle) = 0;
    virtual uint GetHandle() const = 0;
};
} 


#endif