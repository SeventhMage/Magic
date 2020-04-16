#ifndef _MAGIC_I_BUFFEROBJECT_H_
#define _MAGIC_I_BUFFEROBJECT_H_

namespace magic
{
class IBufferObject
{
public:
    enum BufferObjectType
    {
        GPU = 0,
        CPU = 1,
    };
    virtual ~IBufferObject(){}

    virtual void Bind() = 0;
    virtual void UnBind() = 0;
};
}

#endif
