#ifndef _MAGIC_MATH_CPLANE3D_H_
#define _MAGIC_MATH_CPLANE3D_H_

#include "CVector3.h"

namespace magic
{
class CPlane3
{
public:
	CPlane3() : m_vNormal(0, 1.0f, 0), m_fDistance(0) {}
	CPlane3(const CVector3 &vNormal, float fDis) : m_vNormal(vNormal), m_fDistance(fDis) {}
	CPlane3(const CVector3 &vPos1, const CVector3 &vPos2, const CVector3 &vPos3)
	{
		SetPlane(vPos1, vPos2, vPos3);
	}

	~CPlane3() {}

	void SetPlane(const CVector3 &vNormal, float fDis)
	{
		m_vNormal = vNormal;
		m_fDistance = fDis;
	}

	void SetPlane(const CVector3 &vPos1, const CVector3 &vPos2, const CVector3 &vPos3)
	{
		CVector3 v1 = vPos2 - vPos1;
		CVector3 v2 = vPos3 - vPos1;
		m_vNormal = v1.crossProduct(v2);
		m_vNormal.normalize();
		m_fDistance = vPos1.dotProduct(m_vNormal);
	}

	void SetPlane(const CVector3 &vPoint, const CVector3 &vNormal)
	{
		m_fDistance = vPoint.dotProduct(vNormal);
		m_vNormal = vNormal;
	}

	bool Intersection(const CVector3 &vLinePoint1, const CVector3 &vLinePoint2)
	{
		return false;
	}

	float GetDistance(const CVector3 &vPos) const
	{
		return vPos.dotProduct(m_vNormal) - m_fDistance;
	}

	CVector3 GetMemberPoint() const
	{
		return m_vNormal * -m_fDistance;
	}

	CVector3 m_vNormal;
	float m_fDistance;
};
} // namespace magic

#endif