#ifndef _MAGIC_I_OBJECT_H_
#define _MAGIC_I_OBJECT_H_

namespace magic
{
typedef int OID;

static int s_OID = 0;

class IObject
{
public:
    IObject() :_OID(++s_OID) {}
    virtual ~IObject() {}
    virtual OID GetID() const { return _OID; }
private:
    int _OID;
};

} // namespace magic

#endif
