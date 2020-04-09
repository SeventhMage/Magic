#include "CTGAImage.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace magic
{

CTGAImage::CTGAImage()
	: m_iWidth(0), m_iHeight(0), m_iComponents(RGB), m_uFormat(RGB), m_lImageSize(0), m_pData(nullptr)
{
	memset(m_filename, 0, sizeof(m_filename));
}

CTGAImage::~CTGAImage()
{
	if (m_pData)
		free(m_pData);
}

void CTGAImage::Save(const char *filename, char *data, int widht, int height)
{
}

ubyte *CTGAImage::Load(const char *filename)
{
	FILE *pFile;  // File pointer
	short sDepth; // Pixel depth;

	// Attempt to open the file
	pFile = fopen(filename, "rb");
	if (pFile == NULL)
	{
		printf("Openfile %s failed\n", filename);
		return NULL;
	}
	// Read in header (binary)
	fread(&m_tgaHeader, 18 /* sizeof(TGAHEADER)*/, 1, pFile);

	// Do byte swap for big vs little endian
#ifdef __APPLE__
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
	LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
	LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
	LITTLE_ENDIAN_WORD(&tgaHeader.width);
	LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif

	// Get width, height, and depth of texture
	m_iWidth = m_tgaHeader.width;
	m_iHeight = m_tgaHeader.height;
	sDepth = m_tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (m_tgaHeader.bits != 8 && m_tgaHeader.bits != 24 && m_tgaHeader.bits != 32)
	{
		return NULL;
	}
	// Calculate size of image buffer
	m_lImageSize = m_tgaHeader.width * m_tgaHeader.height * sDepth;

	// Allocate memory and check for success
	m_pData = (ubyte *)malloc(m_lImageSize * sizeof(ubyte));
	if (m_pData == NULL)
	{
		return NULL;
	}
	// Read in the bits
	// Check for read error. This should catch RLE or other
	// weird formats that I don't want to recognize
	if (fread(m_pData, m_lImageSize, 1, pFile) != 1)
	{
		free(m_pData);
		m_pData = NULL;
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
#ifndef OPENGL_ES
	case 3: // Most likely case
		m_uFormat = BGR;
		m_iComponents = RGB;
		break;
#endif
	case 4:
		m_uFormat = BGRA;
		m_iComponents = RGBA;
		break;
	case 1:
		m_uFormat = LUMINANCE;
		m_iComponents = LUMINANCE;
		break;
	default: // RGB
			 // If on the iPhone, TGA's are BGR, and the iPhone does not
			 // support BGR without alpha, but it does support RGB,
			 // so a simple swizzle of the red and blue bytes will suffice.
			 // For faster iPhone loads however, save your TGA's with an Alpha!
#ifdef OPENGL_ES
		for (int i = 0; i < lImageSize; i += 3)
		{
			GLbyte temp = pBits[i];
			pBits[i] = pBits[i + 2];
			pBits[i + 2] = temp;
		}
#endif
		break;
	}

	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return m_pData;
}

} // namespace magic