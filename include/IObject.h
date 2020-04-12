#ifndef _MAGIC_I_OBJECT_H_
#define _MAGIC_I_OBJECT_H_

namespace magic
{
typedef int OID;

class IObject
{
public:
    virtual ~IObject() {}
    virtual OID GetID() const { return 0; }
};

} // namespace magic

#endif
