#include "CGLES3Renderer.h"


namespace magic
{
CGLES3Renderer::CGLES3Renderer(void *esContextt, const char *title, GLint width, GLint height, GLuint flags)
{
    esCreateWindow((ESContext *)esContextt, title, width, height, flags);
}
}
