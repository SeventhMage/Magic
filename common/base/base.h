#ifndef _MAGIC_COMMON_BASE_BASE_H_
#define _MAGIC_COMMON_BASE_BASE_H_

#include "StringHelper.h"

namespace magic
{
template <typename Type>
inline void Swap(Type &a, Type &b)
{
	Type c = a;
	a = b;
	b = c;
}

inline float InvSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int *)&x;				// get bits for floating VALUE
	i = 0x5f375a86 - (i >> 1);		// gives initial guess y0
	x = *(float *)&i;				// convert bits BACK to float
	x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
	return x;
}

inline float Square(float x)
{
	return (x * x);
}

inline float Random(float a, float b)
{
	float r = 1.f * rand() / RAND_MAX;
	return (a + r * (b - a));
}
} // namespace magic

#endif