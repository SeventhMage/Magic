#ifndef _MAGIC_GLES_DEBUG_H_
#define _MAGIC_GLES_DEBUG_H_

#include <stdio.h>
#include <assert.h>
#include "gl3.h"

namespace magic
{
inline void DebugGLError(const char *filename, int lineNum)
{
	GLenum err = glGetError();
	if (err)
	{
		switch (err)
		{
		case GL_INVALID_ENUM:
			printf("File Line Number[%s:%d] GL_INVALID_ENUM\n", filename, lineNum);
			break;
		case GL_INVALID_VALUE:
			printf("File Line Number[%s:%d] GL_INVALID_VALUE\n", filename, lineNum);
			break;
		case GL_INVALID_OPERATION:
			printf("File Line Number[%s:%d] GL_INVALID_OPERATION\n", filename, lineNum);
			break;
		case GL_OUT_OF_MEMORY:
			printf("File Line Number[%s:%d] GL_OUT_OF_MEMORY\n", filename, lineNum);
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printf("File Line Number[%s:%d] GL_INVALID_FRAMEBUFFER_OPERATION\n", filename, lineNum);
			break;
		default:
			printf("File Line Number[%s:%d] unknown error\n", filename, lineNum);
			break;
		}
		assert(0);
	}
}
#ifdef DEBUG
#define GLDebug(Func) \
	Func;             \
	DebugGLError(__FILE__, __LINE__);
#else
#define GLDebug(Func) Func;
#endif

inline void CheckGLFBOStatus(const char *filename, int lineNum, GLenum target)
{
	GLenum fboStatus = glCheckFramebufferStatus(target);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
	{
		switch (fboStatus)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			printf("File Line Number[%s:%d] GL_FRAMEBUFFER_UNDEFINED\n", filename, lineNum);
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			printf("File Line Number[%s:%d] GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n", filename, lineNum);
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			printf("File Line Number[%s:%d] GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n", filename, lineNum);
			break;
			/*
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			printf("File Line Number[%s:%d] GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n", filename, lineNum);
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			printf("File Line Number[%s:%d] GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n", filename, lineNum);
			break;
			*/
		case GL_FRAMEBUFFER_UNSUPPORTED:
			printf("File Line Number[%s:%d] GL_FRAMEBUFFER_UNSUPPORTED\n", filename, lineNum);
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			printf("File Line Number[%s:%d] GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n", filename, lineNum);
			break;
			/*
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			printf("File Line Number[%s:%d] GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS\n", filename, lineNum);
			break;
			*/
		default:
			printf("File Line Number[%s:%d] unknown error\n", filename, lineNum);
			break;
		}
		assert(0);
	}
}
#ifdef _DEBUG
#define GLCheckFBOStatus(target) CheckGLFBOStatus(__FILE__, __LINE__, (target));
#else
#define GLCheckFBOStatus
#endif
} // namespace magic

#endif
