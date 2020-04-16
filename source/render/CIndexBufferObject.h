#ifndef _MAGIC_C_INDEXBUFFEROBJECT_H_
#define _MAGIC_C_INDEXBUFFEROBJECT_H_

#include "render/IBufferObject.h"

namespace magic
{
class CIndexBufferObject : public IBufferObject
{
public:
    CIndexBufferObject() {}
    virtual ~CIndexBufferObject() {}

    virtual void BufferData(void *indices, int idsSize) {}
    virtual void BufferSubData(void *data, int size, int offset) {}

    //GPUBufferType GetBufferType(){ return GBT_INDEX; };
    virtual int GetMode() { return 0; }
    virtual int GetIndicesNum() { return 0; }
    virtual int GetIndexType() { return 0; }

private:
};
} // namespace magic

#endif
