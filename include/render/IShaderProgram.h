#ifndef _MAGIC_RENDER_ISHADERPROGRAM_H_
#define _MAGIC_RENDER_ISHADERPROGRAM_H_

namespace magic
{
class IShaderProgram
{
public:
    virtual ~IShaderProgram();

    virtual void BindShaderParam() = 0;
};
}

#endif