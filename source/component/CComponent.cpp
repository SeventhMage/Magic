#include "component/CComponent.h"

namespace magic
{
CComponent::CComponent()
    : m_ID(++m_sIDCount)
{
}

void CComponent::Update()
{
}
} // namespace magic