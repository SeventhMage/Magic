#include "CGLES3Texture.h"
#include "GLESDebug.h"
#include "GLESType.h"

namespace magic
{

CGLES3Texture::CGLES3Texture()
{
	GLDebug(glGenTextures(1, &m_hTexture));
}

CGLES3Texture::~CGLES3Texture()
{
	GLDebug(glDeleteTextures(1, &m_hTexture));
}

void CGLES3Texture::Create2D(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data)
{
	m_target = GL_TEXTURE_2D;
	GLDebug(glBindTexture(GL_TEXTURE_2D, m_hTexture));

	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLDebug(glTexImage2D(GL_TEXTURE_2D, 0, GetGLColorFormat(internalformat), width, height, 0, GetGLColorFormat(format), GetGLPixelType(type), data));

	//GLDebug(glGenerateMipmap(GL_TEXTURE_2D));

	GLDebug(glBindTexture(GL_TEXTURE_2D, 0));
}

void CGLES3Texture::CreateCube(EColorFormat internalformat, int width, int height, EColorFormat format, EPixelType type, void *data[6])
{
	m_target = GL_TEXTURE_CUBE_MAP;

	GLDebug(glBindTexture(GL_TEXTURE_CUBE_MAP, m_hTexture));
	GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (int i = 0; i < 6; i++)
	{
		GLDebug(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GetGLColorFormat(internalformat), width, height, 0,
							 GetGLColorFormat(format), GetGLPixelType(type), data[i]));
	}
	GLDebug(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
	GLDebug(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

void CGLES3Texture::CreateDepth(int width, int height)
{
	m_target = GL_TEXTURE_2D;
	GLDebug(glBindTexture(GL_TEXTURE_2D, m_hTexture));
	GLDebug(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
}

void CGLES3Texture::Bind(uint slot)
{
	GLDebug(glActiveTexture(GL_TEXTURE0 + slot));
	GLDebug(glBindTexture(m_target, m_hTexture));
}

void CGLES3Texture::UnBind()
{
	GLDebug(glBindTexture(m_target, 0));
}

void CGLES3Texture::Create(uint target, uint handle)
{
	m_target = target;
	m_hTexture = handle;
}

} // namespace magic
