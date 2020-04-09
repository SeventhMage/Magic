#ifndef _MX_RENDER_OPENGL_TYPE_H_
#define _MX_RENDER_OPENGL_TYPE_H_

#include "resource/IShader.h"
#include "render/ITexture.h"
#include "magicType.h"
#include "gl3.h"

namespace magic
{
static GLenum GetGLShaderType(EShaderType shaderType)
{
	switch (shaderType)
	{
	case EShaderType::Vertex:
		return GL_VERTEX_SHADER;
		break;
	case EShaderType::Fragment:
		return GL_FRAGMENT_SHADER;
		break;
	default:
		break;
	}
	return 0;
}

static int GetUniformTypeSize(GLenum type)
{
	switch (type)
	{
	case GL_INT:
		return 4;
	case GL_FLOAT:
		return 4;
	case GL_FLOAT_VEC2:
		return 8;
	case GL_FLOAT_VEC3:
		return 12;
	case GL_FLOAT_VEC4:
		return 16;
	case GL_FLOAT_MAT4:
		return 64;
	case GL_TEXTURE:
		return 4;
	default:;
	}
	return 0;
}

static GLenum GetGLColorFormat(EColorFormat format)
{
	switch (format)
	{
	case EColorFormat::ALPHA:
		return GL_ALPHA;
	case EColorFormat::RGB:
		return GL_RGB;
	case EColorFormat::RGBA:
		return GL_RGBA;
	case EColorFormat::RGB16F:
		return GL_RGB16F;
	case EColorFormat::RGBA16F:
		return GL_RGBA16F;
	case EColorFormat::BGR:
		return GL_BGR;
	case EColorFormat::BGRA:
		return GL_BGRA;
	case EColorFormat::LUMINANCE:
		return GL_LUMINANCE;
	default:
		return GL_RGB;
	}
}

static GLenum GetGLPixelType(EPixelType type)
{
	switch (type)
	{
	case EPixelType::UNSIGNED_BYTE:
		return GL_UNSIGNED_BYTE;
	case EPixelType::UNSIGNED_SHORT_5_6_5:
		return GL_UNSIGNED_SHORT_5_6_5;
	case EPixelType::UNSIGNED_SHORT_4_4_4_4:
		return GL_UNSIGNED_SHORT_4_4_4_4;
	case EPixelType::UNSIGNED_SHORT_5_5_5_1:
		return GL_UNSIGNED_SHORT_5_5_5_1;
	default:
		return GL_UNSIGNED_BYTE;
	}
}

} // namespace magic

#endif