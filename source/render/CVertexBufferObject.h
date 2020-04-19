#ifndef _MAGIC_CVERTEXBUFFEROBJECT_H_
#define _MAGIC_CVERTEXBUFFEROBJECT_H_

#include "render/IBufferObject.h"


namespace magic
{
class CVertexBufferObject : public IBufferObject
{
public:
    CVertexBufferObject();
    virtual ~CVertexBufferObject() {}

    virtual void BufferData(void *data, int size) {}
    virtual void BufferSubData(void *data, int size, int offset) {}
};
} // namespace magic

#endif

