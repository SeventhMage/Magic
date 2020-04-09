#ifndef _MAGIC_I_MAGE_H_
#define _MAGIC_I_MAGE_H_

#include "IResource.h"
#include "base/magicType.h"

namespace magic
{

enum EColorFormat
{
	ALPHA,
	RGB,
	RGBA,
	RGB16F,
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

class IImage : public IResource
{
public:
	virtual ~IImage() {}

	virtual ubyte *Load(const char *filename) = 0;
	virtual void Save(const char *filename, char *data, int widht, int height) = 0;
	virtual ubyte *GetData() = 0;
	virtual EColorFormat GetFormat() const = 0;
	virtual ulong GetImageSize() const = 0;
	virtual EColorFormat GetComponents() const = 0;
	virtual EPixelType GetPixelType() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};
} // namespace magic

#endif