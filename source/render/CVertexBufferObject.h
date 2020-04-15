#ifndef _MAGIC_CVERTEXBUFFEROBJECT_H_
#define _MAGIC_CVERTEXBUFFEROBJECT_H_

#include "render/IBufferObject.h"


namespace magic
{
class CVertexBufferObject : public IBufferObject
{
public:
    CVertexBufferObject(int first, int count, int mode);
    virtual ~CVertexBufferObject() {}

    virtual void BufferData(void *data, int size) {}
    virtual void BufferSubData(void *data, int size, int offset) {}
    virtual int GetMode() const { return m_mode; }
    virtual int GetVerticesCount() const { return m_count; }
    virtual int GetFirstIndex() const { return m_first; }

private:
    int m_first;
    int m_count;
    int m_mode;
};
} // namespace magic

#endif

