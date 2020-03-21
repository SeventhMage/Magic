#ifndef _MAGIC_RENDER_IBUFFER_H_
#define _MAGIC_RENDER_IBUFFER_H_

namespace magic
{
class IBuffer
{
public:
    enum BufferType
    {
        GPU = 0,
        CPU = 1,
    };
    virtual ~IBuffer(){}

};
}

#endif