#ifndef _MAGIC_MATH_CBOUNDINGBOX_H_
#define _MAGIC_MATH_CBOUNDINGBOX_H_

#include "CVector3.h"

namespace magic
{
class CBoundingBox
{
public:
	CBoundingBox() : m_minEdge(-1, -1, -1), m_maxEdge(1, 1, 1) {}
	CBoundingBox(const CVector3 &minEdge, const CVector3 &maxEdge) : m_minEdge(minEdge), m_maxEdge(maxEdge) {}
	~CBoundingBox() {}

	CVector3 m_minEdge;
	CVector3 m_maxEdge;
};
} // namespace magic

#endif
