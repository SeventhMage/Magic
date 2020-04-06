#ifndef _MAGIC_C_VECTOR4_
#define _MAGIC_C_VECTOR4_

#include "base/base.h"

namespace magic
{
class CVector4
{
public:
	CVector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	CVector4() : x(0), y(0), z(0), w(0) {}

	union {
		float v[4];
		struct
		{
			float x, y, z, w;
		};
	};
};
}

#endif
