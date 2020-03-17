#ifndef _MAGIC_RENDER_ITEXTURE_H_
#define _MAGIC_RENDER_ITEXTURE_H_

namespace magic
{
class ITexture
{
public:
    virtual ~ITexture(){}

    virtual void BindTexture() = 0;
};
} 


#endif