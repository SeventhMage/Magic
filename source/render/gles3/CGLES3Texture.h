#ifndef _MAGIC_CGLES3TEXTURE_H_
#define _MAGIC_CGLES3TEXTURE_H_

#include "render/ITexture.h"

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

namespace magic
{
class CGLES3Texture: public ITexture
{
public:
	CGLES3Texture();
	virtual ~CGLES3Texture();

	virtual void Bind(uint slot = 0);
	virtual void UnBind();
	virtual void Create2D(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data);
	virtual void CreateCube(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data[6]);
	virtual void CreateDepth(int width, int height);
	virtual void Create(uint target, uint handle);
	virtual uint GetHandle() const { return m_hTexture; }

private:
	uint m_hTexture;
	GLenum m_target;
};
} // namespace mx

#endif
