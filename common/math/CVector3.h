#ifndef _MX_CORE_CVECTOR3_H_
#define _MX_CORE_CVECTOR3_H_

#include <math.h>
#include "magicDef.h"

namespace magic
{
class CVector3
{
public:
	CVector3() : x(0), y(0), z(0) {}
	CVector3(float x, float y, float z) : x(x), y(y), z(z) {}

	CVector3 operator-() const { return CVector3(-x, -y, -z); }

	CVector3 operator=(const CVector3 &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	CVector3 operator+(const CVector3 &other) const { return CVector3(x + other.x, y + other.y, z + other.z); }
	CVector3 &operator+=(const CVector3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	CVector3 operator-(const CVector3 &other) const { return CVector3(x - other.x, y - other.y, z - other.z); }
	CVector3 &operator-=(const CVector3 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	CVector3 operator*(const float v) const { return CVector3(x * v, y * v, z * v); }
	CVector3 operator*(const CVector3 &other) const { return CVector3(x * other.x, y * other.y, z * other.z); }
	CVector3 &operator*=(const float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	CVector3 operator/(const float v) const
	{
		float tmp = (float)(1.0 / v);
		return CVector3(x * tmp, y * tmp, z * tmp);
	}
	CVector3 &operator/=(const float v)
	{
		float tmp = (float)(1.0 / v);
		x *= tmp;
		y *= tmp;
		z *= tmp;
		return *this;
	}
	CVector3 operator/(const CVector3 &other) const { return CVector3(x / other.x, y / other.y, z / other.z); }

	bool operator==(const CVector3 &other) const { return equals(other); }
	bool operator!=(const CVector3 &other) const { return !equals(other); }

	bool equals(const CVector3 &other) const
	{
		return FLOAT_EQUAL(x, other.x) && FLOAT_EQUAL(y, other.y) && FLOAT_EQUAL(z, other.z);
	}

	CVector3 &set(const float nx, const float ny, const float nz)
	{
		x = nx;
		y = ny;
		z = nz;
		return *this;
	}
	CVector3 &set(const CVector3 &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	float getLength() const { return static_cast<float>(sqrt(x * x + y * y + z * z)); }
	float getLengthSQ() const { return x * x + y * y + z * z; }

	float dotProduct(const CVector3 &other) const { return x * other.x + y * other.y + z * other.z; }
	CVector3 crossProduct(const CVector3 &other) const
	{
		return CVector3(y * other.z - other.y * z, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	float getDistanceFrom(const CVector3 &other) const
	{
		return CVector3(x - other.x, y - other.y, z - other.z).getLength();
		//return static_cast<float>(sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z)));
	}

	float getDistanceFromSQ(const CVector3 &other) const
	{
		return CVector3(x - other.x, y - other.y, z - other.z).getLengthSQ();
		// return static_cast<float>((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));
	}

	CVector3 &normalize()
	{
		double length = static_cast<double>(x * x + y * y + z * z);
		if (0 == length)
			return *this;
		length = 1 / sqrt(length);
		x *= static_cast<float>(length);
		y *= static_cast<float>(length);
		z *= static_cast<float>(length);
		return *this;
	}

	CVector3 &setLength(float length)
	{
		normalize();
		return (*this *= length);
	}

	CVector3 &invert()
	{
		x *= -1;
		y *= -1;
		z *= -1;
		return *this;
	}

	void rotateXZBy(double radians, const CVector3 &center = CVector3(0, 1.0f, 0))
	{
		double cs = cos(radians);
		double sn = sin(radians);
		x -= center.x;
		z -= center.z;
		set((float)(x * cs + z * sn), y, (float)(-x * sn + z * cs));
		x += center.x;
		z += center.z;
	}

	//Left-handed coordinate system is the same as right-handed coordinate system.
	void rotateXYBy(double radians, const CVector3 &center = CVector3(0, 0, 1.0f))
	{
		double cs = cos(radians);
		double sn = sin(radians);

		x -= center.x;
		y -= center.y;
		set((float)(x * cs - y * sn), (float)(x * sn + y * cs), z);
		x += center.x;
		y += center.y;
	}

	//Left-handed coordinate system is the same as right-handed coordinate system.
	void rotateYZBy(double radians, const CVector3 &center = CVector3(1.0f, 0, 0))
	{
		double cs = cos(radians);
		double sn = sin(radians);

		y -= center.y;
		z -= center.z;
		set(x, (float)(y * cs - z * sn), (float)(y * sn + z * cs));
		y += center.y;
		z += center.z;
	}

	void rotateBy(double radians, const CVector3 &axis)
	{
	}

	//CVector3 getInterpolated(const CVector3 &other, double d) const
	//{
	//	const double inv = 1.0 - d;
	//	return CVector3((float)(x * d + other.x * inv), (float)(y * d + other.y * inv));
	//}

	CVector3 &interpolate(const CVector3 &a, const CVector3 &b, double d)
	{
		x = (float)((double)b.x + ((double)(a.x - b.x)) * d);
		y = (float)((double)b.y + ((double)(a.y - b.y)) * d);
		z = (float)((double)b.z + ((double)(a.z - b.z)) * d);
	}

	//Get the rotations that would make a (0,0,1) direction vector point in the same direction as this direction vector.
	//(0, 0, 1) rotates radians.x radians by x and rotate radians.y radians by y.
	CVector3 getHorizontalAngle() const
	{
		CVector3 radians;

		const double tmp = (atan2((double)x, (double)z));
		radians.y = (float)tmp;

		if (radians.y < 0)
			radians.y += static_cast<float>(PI64 * 2);
		if (radians.y >= static_cast<float>(PI64 * 2))
			radians.y -= static_cast<float>(PI64 * 2);

		const double z1 = sqrt(x * x + z * z);

		radians.x = (float)(atan2((double)z1, (double)y) - PI64 * 0.5);

		if (radians.x < 0)
			radians.x += static_cast<float>(PI64 * 2);
		if (radians.x >= static_cast<float>(PI64 * 2))
			radians.x -= static_cast<float>(PI64 * 2);

		return radians;
	}

	// Builds a direction vector from (this) rotation vector.
	CVector3 rotationToDirection(const CVector3 &forwards = CVector3(0, 0, 1)) const
	{
		const double cr = cos(x);
		const double sr = sin(x);
		const double cp = cos(y);
		const double sp = sin(y);
		const double cy = cos(z);
		const double sy = sin(z);

		const double srsp = sr * sp;
		const double crsp = cr * sp;

		const double pseudoMatrix[] = {
			(cp * cy), (cp * sy), (-sp),
			(srsp * cy - cr * sy), (srsp * sy + cr * cy), (sr * cp),
			(crsp * cy + sr * sy), (crsp * sy - sr * cy), (cr * cp)};

		return CVector3(
			(float)(forwards.x * pseudoMatrix[0] +
					forwards.y * pseudoMatrix[3] +
					forwards.z * pseudoMatrix[6]),
			(float)(forwards.x * pseudoMatrix[1] +
					forwards.y * pseudoMatrix[4] +
					forwards.z * pseudoMatrix[7]),
			(float)(forwards.x * pseudoMatrix[2] +
					forwards.y * pseudoMatrix[5] +
					forwards.z * pseudoMatrix[8]));
	}

	union {
		float v[3];
		struct
		{
			float x, y, z;
		};
	};
};

inline CVector3 operator*(const float scalar, const CVector3 &vector) { return vector * scalar; }
} // namespace magic

#endif