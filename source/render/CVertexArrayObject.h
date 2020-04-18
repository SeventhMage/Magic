#ifndef _MAGIC_C_VERTEX_ARRAY_OBJECT_H_
#define _MAGIC_C_VERTEX_ARRAY_OBJECT_H_

#include "render/IBufferObject.h"

namespace magic
{
class CVertexArrayObject : public IBufferObject
{
public:
    CVertexArrayObject() {}
    virtual ~CVertexArrayObject() {}
    virtual void EnableVertexAttrib(int vertexArrayIndex, int vertType, int stride, int offset) {}
};
} // namespace magic

#endif
