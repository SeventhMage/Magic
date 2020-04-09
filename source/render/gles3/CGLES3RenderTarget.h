#ifndef _MAGIC_C_GLES3RENDERTARGET_H_
#define _MAGIC_C_GLES3RENDERTARGET_H_

#include "render/IRenderTarget.h"
#include "CGLES3Texture.h"

#include <map>

namespace magic
{

class CGLES3RenderTarget : public IRenderTarget
{
public:
	CGLES3RenderTarget(int textureCount, int width, int height, bool bHaveDepth = false);
	~CGLES3RenderTarget();
	virtual void BeginTarget();
	virtual void EndTarget();
	virtual ITexture *GetBindTexture(int index) const;
	virtual ITexture *GetDepthTexture() const;
	virtual ITexture *GetTexture(int index) const;

private:
	std::vector<ITexture *> m_bindTexture;
	ITexture *m_depthTexture;
	int m_iWidth;
	int m_iHeight;
	GLuint m_fbo;
	int m_textureCount;
};

} // namespace magic

#endif
