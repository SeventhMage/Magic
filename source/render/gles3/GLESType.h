#ifndef _MX_RENDER_OPENGL_TYPE_H_
#define _MX_RENDER_OPENGL_TYPE_H_

#include "IShader.h"
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

} // namespace magic

#endif