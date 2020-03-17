#ifndef _MX_CORE_CVECTOR2_H_
#define _MX_CORE_CVECTOR2_H_

#include "base/base.h"

#include <math.h>

namespace magic
{
class CVector2
{
public:
	CVector2(float x, float y) : x(x), y(y) {}
	CVector2() : x(0), y(0) {}
	inline float getLength() const { return (sqrtf(x * x + y * y)); }
	inline float getDistanceFrom(const CVector2 &other) const
	{
		return CVector2(x - other.x, y - other.y).getLength();
	}

	inline float getInvLength() const { return (InvSqrt(x * x + y * y)); }
	inline float getInvDistanceFrom(const CVector2 &other) const
	{
		return CVector2(x - other.x, y - other.y).getInvLength();
	}

	CVector2 operator*(const float v) const { return CVector2(x * v, y * v); }
	friend CVector2 operator*(const float v, const CVector2 &vec) { return CVector2(vec.x * v, vec.y * v); }
	CVector2 operator/(const float v) const { return CVector2(x / v, y / v); }
	CVector2 operator+(const CVector2 &other)
	{
		return CVector2(x + other.x, y + other.y);
	}
	union {
		float v[2];
		struct
		{
			float x, y;
		};
	};
};
} // namespace magic

#endif