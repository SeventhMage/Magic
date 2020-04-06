#ifndef _MAGIC_I_OBJECT_H_
#define _MAGIC_I_OBJECT_H_

namespace magic
{
typedef int OID;

class IObject
{
public:
    IObject() { m_OID = ++s_IDCount; }
    virtual ~IObject() {}
    virtual OID GetID() const { return m_OID; }

private:
    static OID s_IDCount;
    int m_OID;
};
OID IObject::s_IDCount = 0;
} // namespace magic

#endif