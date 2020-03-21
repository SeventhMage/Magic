#ifndef _MAGIC_C_COMPONENT_H_
#define _MAGIC_C_COMPONENT_H_

#include "IComponent.h"

namespace magic
{
class CComponent : public IComponent
{
public:
    CComponent();
    virtual int GetID() const { return m_ID; }
    virtual void Update();
private:
    static int m_sIDCount;
    int m_ID;
};
} // namespace magic

#endif