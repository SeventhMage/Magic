#ifndef _MAGIC_MATH_C_RAY_H_
#define _MAGIC_MATH_C_RAY_H_
/************************************************************************/
/* 射线                                                                 */
/************************************************************************/

#include "CVector3.h"

namespace magic
{
class CRay
{
public:
	CRay(const CVector3 &origin, const CVector3 &direction)
		: m_origin(origin), m_direction(direction) {}
	CRay() {}
	~CRay() {}
	const CVector3 &GetOrigin() const { return m_origin; }
	const CVector3 &GetDirection() const { return m_direction; }

private:
	CVector3 m_origin;
	CVector3 m_direction;
};
} // namespace magic

#endif