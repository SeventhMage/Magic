#ifndef _MX_RENDER_OPENGL_TYPE_H_
#define _MX_RENDER_OPENGL_TYPE_H_

#include "resource/IShader.h"
#include "render/ERender.h"
#include "base/magicType.h"
#include "base/Log.h"
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
    case GL_SAMPLER_2D:
        return 4;
    case GL_SAMPLER_CUBE:
        return 4;
	default:;
	}
    LogError("GetUniformTypeSize type not find : %x\n", type);
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
	/*
		return GL_BGR;
	case EColorFormat::BGRA:
		return GL_BGRA;
		*/
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
    case EPixelType::PIXEL_UNSIGNED_BYTE:
		return GL_UNSIGNED_BYTE;
	case EPixelType::PIXEL_UNSIGNED_SHORT_5_6_5:
		return GL_UNSIGNED_SHORT_5_6_5;
	case EPixelType::PIXEL_UNSIGNED_SHORT_4_4_4_4:
		return GL_UNSIGNED_SHORT_4_4_4_4;
	case EPixelType::PIXEL_UNSIGNED_SHORT_5_5_5_1:
		return GL_UNSIGNED_SHORT_5_5_5_1;
    case EPixelType::PIXEL_FLOAT:
        return GL_FLOAT;
	default:
		return GL_UNSIGNED_BYTE;
	}
}

static int GetGLColorMask(int mask)
{
	int result = 0;
	if (mask & MAGIC_DEPTH_BUFFER_BIT)
		result |= GL_DEPTH_BUFFER_BIT;
	if (mask & MAGIC_STENCIL_BUFFER_BIT)
		result |= GL_STENCIL_BUFFER_BIT;
	if (mask & MAGIC_COLOR_BUFFER_BIT)
		result |= GL_COLOR_BUFFER_BIT;
	return result;
}

static GLenum GetGLVariableType(VariableType vat)
{
	switch (vat)
	{
	case BYTE:
		return GL_BYTE;
	case UBYTE:
		return GL_UNSIGNED_BYTE;
	case SHORT:
		return GL_SHORT;
	case USHORT:
		return GL_UNSIGNED_SHORT;
	case INT:
		return GL_INT;
	case UINT:
		return GL_UNSIGNED_INT;
	case FIXED:
		return GL_FIXED;
	case FLOAT:
		return GL_FLOAT;
	case HALF_FLOAT:
		return GL_HALF_FLOAT;
	//case DOUBLE:
	//return GL_DOUBLE;
	case INT_2_10_10_10_REV:
		return GL_INT_2_10_10_10_REV;
	case UINT_2_10_10_10_REV:
		return GL_UNSIGNED_INT_2_10_10_10_REV;
	default:
		break;
	}
	return GL_FLOAT;
}

static int GetGLVariableSize(int vat)
{
	switch (vat)
	{
	case GL_BYTE:
		return 1;
	case GL_UNSIGNED_BYTE:
		return 1;
	case GL_SHORT:
		return 2;
	case GL_UNSIGNED_SHORT:
		return 2;
	case GL_INT:
		return 4;
	case GL_UNSIGNED_INT:
		return 4;
	case GL_FIXED:
		return 4;
	case GL_FLOAT:
		return 4;
	case GL_HALF_FLOAT:
		return 4;
	//case GL_DOUBLE:
	//return 8;
	case GL_INT_2_10_10_10_REV:
		return 4;
	case GL_UNSIGNED_INT_2_10_10_10_REV:
		return 4;
	default:
		break;
	}
	return 4;
}

static uint GetVariableSize(VariableType vat)
{
	switch (vat)
	{
	case BYTE:
		return 1;
	case UBYTE:
		return 1;
	case SHORT:
		return 2;
	case USHORT:
		return 2;
	case INT:
		return 4;
	case UINT:
		return 4;
	case FIXED:
		return 4;
	case FLOAT:
		return 4;
	case HALF_FLOAT:
		return 4;
	case DOUBLE:
		return 8;
	case INT_2_10_10_10_REV:
		return 4;
	case UINT_2_10_10_10_REV:
		return 4;
	default:
		break;
	}
	return 4;
}

static int GetGLGPUBufferMode(GPUBufferMode mode)
{
	switch (mode)
	{
	case GBM_LINES:
		return GL_LINES;
	case GBM_POINTS:
		return GL_POINTS;
	case GBM_TRIANGLES:
		return GL_TRIANGLES;
	case GBM_TRIANGLE_STKIP:
		return GL_TRIANGLE_STRIP;
	case GBM_TRIANGLE_FAN:
		return GL_TRIANGLE_FAN;
	default:;
	}
	return GL_TRIANGLES;
}

static int GetGLGPUBufferUsage(GPUBufferUsage usage)
{
	switch (usage)
	{
	case GBU_STREAM_DRAW:
		return GL_STREAM_DRAW;
	case GBU_STREAM_READ:
		return GL_STREAM_READ;
	case GBU_STREAM_COPY:
		return GL_STREAM_COPY;
	case GBU_STATIC_DRAW:
		return GL_STATIC_DRAW;
	case GBU_STATIC_READ:
		return GL_STATIC_READ;
	case GBU_STATIC_COPY:
		return GL_STATIC_COPY;
	case GBU_DYNAMIC_DRAW:
		return GL_DYNAMIC_DRAW;
	case GBU_DYNAMIC_READ:
		return GL_DYNAMIC_READ;
	case GBU_DYNAMIC_COPY:
		return GL_DYNAMIC_COPY;
	default:;
	}
	return GL_DYNAMIC_DRAW;
}

} // namespace magic

#endif
