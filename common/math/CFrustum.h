#ifndef _MAGIC_MATH_CFRUSTUM_H_
#define _MAGIC_MATH_CFRUSTUM_H_

#include "CPlane3.h"
#include "CVector3.h"
#include "CMatrix4.h"
#include "CBoundingBox.h"

namespace magic
{
class CFrustum
{
public:
	enum FPLANES
	{
		F_FAR_PLANE = 0,
		F_NEAR_PLANE,
		F_LEFT_PLANE,
		F_RIGHT_PLANE,
		F_BOTTOM_PLANE,
		F_TOP_PLANE,

		F_PLANE_COUNT
	};
	CFrustum() {}
	~CFrustum() {}

	void Create(float fFov, float fAspect, float fNear, float fFar)
	{
		float xmin, xmax, ymin, ymax;
		float xFmin, xFmax, yFmin, yFmax;

		fNear = -fNear;
		fFar = -fFar;

		ymax = fNear * float(tan(fFov * 0.5f));
		ymin = -ymax;
		xmin = ymin * fAspect;
		xmax = -xmin;

		yFmax = fFar * float(tan(fFov * 0.5f));
		yFmin = -yFmax;
		xFmin = yFmin * fAspect;
		xFmax = -xFmin;

		m_vNLB.x = xmin;
		m_vNLB.y = ymin;
		m_vNLB.z = fNear;

		m_vNRB.x = xmax;
		m_vNRB.y = ymin;
		m_vNRB.z = fNear;

		m_vNRT.x = xmax;
		m_vNRT.y = ymax;
		m_vNRT.z = fNear;

		m_vNLT.x = xmin;
		m_vNLT.y = ymax;
		m_vNLT.z = fNear;

		m_vFLB.x = xFmin;
		m_vFLB.y = yFmin;
		m_vFLB.z = fFar;

		m_vFRB.x = xFmax;
		m_vFRB.y = yFmin;
		m_vFRB.z = fFar;

		m_vFRT.x = xFmax;
		m_vFRT.y = yFmax;
		m_vFRT.z = fFar;

		m_vFLT.x = xFmin;
		m_vFLT.y = yFmax;
		m_vFLT.z = fFar;

		CreatePlane();
	}

	bool Cull(const CBoundingBox &box) const
	{
		return true;
	}

	bool CullSphere(const CVector3 &pos, float radius) const
	{
		/*				if (pos.z + radius < -m_vFLB.z || pos.z - radius > -m_vNLB.z)
					return true;
				float testX = 0.5f * (m_vNRT.x - m_vNLT.x) * pos.z / -m_vNLT.z;
				if (pos.x - radius > testX || pos.x + radius < -testX)
					return true;
				float testY = 0.5f * (m_vNRT.y - m_vNRB.y) * pos.z / -m_vNLT.z;
				if (pos.y - radius > testY || pos.y + radius < -testY)
					return true;	*/

		for (uint i = 0; i < F_PLANE_COUNT; ++i)
		{
			float dis = m_planeClip[i].GetDistance(pos);
			if (dis < -radius)
				return true;
		}

		return false;
	}

	void Transform(const CMatrix4 &mat4)
	{
		for (uint i = 0; i < F_PLANE_COUNT; ++i)
		{
			mat4.TransformPlane(m_planeClip[i]);
		}
	}

private:
	void CreatePlane()
	{
		//right hand
		m_planeClip[F_NEAR_PLANE].SetPlane(m_vNRB, m_vNLB, m_vNRT);
		m_planeClip[F_FAR_PLANE].SetPlane(m_vFLB, m_vFRB, m_vFRT);
		m_planeClip[F_LEFT_PLANE].SetPlane(m_vNLB, m_vFLB, m_vNLT);
		m_planeClip[F_RIGHT_PLANE].SetPlane(m_vNRB, m_vFRT, m_vFRB);
		m_planeClip[F_TOP_PLANE].SetPlane(m_vNLT, m_vFRT, m_vNRT);
		m_planeClip[F_BOTTOM_PLANE].SetPlane(m_vFRB, m_vFLB, m_vNLB);
	}

private:
	CVector3 m_vNLB;
	CVector3 m_vNRB;
	CVector3 m_vNRT;
	CVector3 m_vNLT;
	CVector3 m_vFLB;
	CVector3 m_vFRB;
	CVector3 m_vFRT;
	CVector3 m_vFLT;

	CPlane3 m_planeClip[F_PLANE_COUNT];
	;
};

} // namespace magic

#endif