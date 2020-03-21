#ifndef _MAGIC_ICOMPONENT_H_
#define _MAGIC_ICOMPONENT_H_

namespace magic
{
class IComponent
{
public:
    virtual ~IComponent(){}
    virtual int GetID() const = 0;
    virtual void Update() = 0;
};
}

#endif