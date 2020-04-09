#ifndef _MAGIC_C_TGA_IMAGE_H_
#define _MAGIC_C_TGA_IMAGE_H_

#include "resource/IImage.h"

namespace magic
{
#pragma pack(push)
#pragma pack(1)
typedef struct
{
	char identsize;				   // Size of ID field that follows header (0)
	char colorMapType;			   // 0 = None, 1 = paletted
	char imageType;				   // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short colorMapStart;  // First colour map entry
	unsigned short colorMapLength; // Number of colors
	unsigned char colorMapBits;	   // bits per palette entry
	unsigned short xstart;		   // image x origin
	unsigned short ystart;		   // image y origin
	unsigned short width;		   // width in pixels
	unsigned short height;		   // height in pixels
	char bits;					   // bits per pixel (8 16, 24, 32)
	char descriptor;			   // image descriptor
} TGAHEADER;
#pragma pack(pop)

class CTGAImage : public IImage
{
public:
	CTGAImage();
	~CTGAImage();

	virtual ubyte *Load(const char *filename);
	virtual void Save(const char *filename, char *data, int widht, int height);
	virtual ubyte *GetData() { return m_pData; }
	virtual EColorFormat GetFormat() const { return m_uFormat; }
	virtual ulong GetImageSize() const { return m_lImageSize; }
	virtual EColorFormat GetComponents() const { return m_iComponents; }
	virtual int GetWidth() const { return m_iWidth; }
	virtual int GetHeight() const { return m_iHeight; }
	virtual EPixelType GetPixelType() const { return UNSIGNED_BYTE; }

private:
	char m_filename[256];
	TGAHEADER m_tgaHeader;
	unsigned long m_lImageSize;
	int m_iWidth;
	int m_iHeight;
	EColorFormat m_iComponents;
	EColorFormat m_uFormat;
	ubyte *m_pData;
};
} // namespace magic

#endif