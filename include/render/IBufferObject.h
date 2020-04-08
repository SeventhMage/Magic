#ifndef _MAGIC_RENDER_IBUFFER_H_
#define _MAGIC_RENDER_IBUFFER_OBJECT_H_

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
    virtual int GetMode() const = 0;
    virtual int GetVerticesCount() const = 0;
    virtual int GetValueType() const = 0;
    virtual int GetFirstIndex() const = 0;
};
}

#endif