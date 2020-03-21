#ifndef _MAGIC_C_OBJECT_H_
#define _MAGIC_C_OBJECT_H_

namespace magic
{
typedef int OID;

class CObject
{
public:
    CObject();
    virtual ~CObject(){}
    OID GetID() { return m_ID; }
private:
    OID m_ID;
};
} // namespace magic


#endif