#ifndef _MAGIC_RENDER_ITEXTURE_H_
#define _MAGIC_RENDER_ITEXTURE_H_

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
    virtual void BindTextureSlot(int slot);
};
} 


#endif