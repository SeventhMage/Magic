#include "CGLES3RenderTarget.h"
#include "CGLES3Texture.h"
#include "GLESDebug.h"
#include "base/magicDef.h"

#include <string.h>
#include <queue>

namespace magic
{
static const int MAX_TEXTURE_COUNT = 16;
CGLES3RenderTarget::CGLES3RenderTarget(int textureCount, int width, int height, bool bHaveDepth)
	: m_iWidth(width), m_iHeight(height), m_fbo(0), m_textureCount(textureCount), m_depthTexture(nullptr)
{
    GLDebug(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_defaultFrameBuffer));
	GLenum drawBuffers[MAX_TEXTURE_COUNT] = {0};
	if (textureCount > 0 || bHaveDepth)
	{
		GLDebug(glGenFramebuffers(1, &m_fbo));
		GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
		for (int i = 0; i < textureCount; ++i)
		{
			ITexture *pTexture = new CGLES3Texture();
			pTexture->Create2D(RGBA16F, m_iWidth, m_iHeight, RGBA, PIXEL_FLOAT, nullptr);
			pTexture->Bind(0);
			GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, pTexture->GetHandle(), 0));
			pTexture->UnBind();
			m_bindTexture.push_back(pTexture);
			drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
		}

		if (bHaveDepth)
		{
			m_depthTexture = new CGLES3Texture();
			m_depthTexture->CreateDepth(m_iWidth, m_iHeight);
			GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->GetHandle(), 0));
		}
	}

	if (textureCount > 0)
	{
		GLDebug(glDrawBuffers(textureCount, drawBuffers));

		GLCheckFBOStatus(GL_FRAMEBUFFER);
        GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFrameBuffer));
	}
	else if (textureCount == 0 && bHaveDepth)
	{
		GLDebug(glDrawBuffers(1, drawBuffers));
        GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFrameBuffer));
	}
}
CGLES3RenderTarget::~CGLES3RenderTarget()
{
	for (auto texture : m_bindTexture)
	{
		SAFE_DEL(texture);
	}
	SAFE_DEL(m_depthTexture);

	GLDebug(glDeleteFramebuffers(1, &m_fbo));
}
void CGLES3RenderTarget::BeginTarget()
{
    GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
	GLDebug(glClearDepthf(1.0f));
	if (m_depthTexture != nullptr)
	{
		GLDebug(glEnable(GL_POLYGON_OFFSET_FILL));
		GLDebug(glPolygonOffset(4.0f, 100.0f))
	}
}
void CGLES3RenderTarget::EndTarget()
{
	GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFrameBuffer));
	if (m_depthTexture != nullptr)
	{
		GLDebug(glDisable(GL_POLYGON_OFFSET_FILL));
	}
}
ITexture *CGLES3RenderTarget::GetBindTexture(int index) const
{
	return m_bindTexture[index];
}
ITexture *CGLES3RenderTarget::GetDepthTexture() const
{
	return m_depthTexture;
}

} // namespace magic
