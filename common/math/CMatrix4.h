#ifndef _MAGIC_MATH_CMATRIX4_H_
#define _MAGIC_MATH_CMATRIX4_H_

#include <assert.h>
#include <string.h>
#include <float.h>

#include "CVector3.h"
#include "CPlane3.h"
#include "magicType.h"

namespace magic
{
class CMatrix4
{
public:
	CMatrix4() { MakeIdentity(); }
	CMatrix4(float m11, float m12, float m13, float m14,
			 float m21, float m22, float m23, float m24,
			 float m31, float m32, float m33, float m34,
			 float m41, float m42, float m43, float m44)
	{
		m[0] = m11, m[1] = m12, m[2] = m13, m[3] = m14;
		m[4] = m21, m[5] = m22, m[6] = m23, m[7] = m24;
		m[8] = m31, m[9] = m32, m[10] = m33, m[11] = m34;
		m[12] = m41, m[13] = m42, m[14] = m43, m[15] = m44;
	}
	CMatrix4(float m[16])
	{
		for (int i = 0; i < 16; ++i)
		{
			this->m[i] = m[i];
		}
	}

	inline CMatrix4 &MakeIdentity()
	{
		memset(m, 0, sizeof(m));
		m[0] = m[5] = m[10] = m[15] = 1.0f;
		return *this;
	}

	float &operator[](int index)
	{
		return m[index];
	}

	const float &operator[](int index) const
	{
		return m[index];
	}

	float operator()(const uint row, const uint col) const
	{
		return m[row * 4 + col];
	}

	float &operator()(const uint row, const uint col)
	{
		return m[row * 4 + col];
	}

	inline CMatrix4 operator*(const CMatrix4 &other) const
	{
		return CMatrix4(
			m[0] * other[0] + m[1] * other[4] + m[2] * other[8] + m[3] * other[12],
			m[0] * other[1] + m[1] * other[5] + m[2] * other[9] + m[3] * other[13],
			m[0] * other[2] + m[1] * other[6] + m[2] * other[10] + m[3] * other[14],
			m[0] * other[3] + m[1] * other[7] + m[2] * other[11] + m[3] * other[15],

			m[4] * other[0] + m[5] * other[4] + m[6] * other[8] + m[7] * other[12],
			m[4] * other[1] + m[5] * other[5] + m[6] * other[9] + m[7] * other[13],
			m[4] * other[2] + m[5] * other[6] + m[6] * other[10] + m[7] * other[14],
			m[4] * other[3] + m[5] * other[7] + m[6] * other[11] + m[7] * other[15],

			m[8] * other[0] + m[9] * other[4] + m[10] * other[8] + m[11] * other[12],
			m[8] * other[1] + m[9] * other[5] + m[10] * other[9] + m[11] * other[13],
			m[8] * other[2] + m[9] * other[6] + m[10] * other[10] + m[11] * other[14],
			m[8] * other[3] + m[9] * other[7] + m[10] * other[11] + m[11] * other[15],

			m[12] * other[0] + m[13] * other[4] + m[14] * other[8] + m[15] * other[12],
			m[12] * other[1] + m[13] * other[5] + m[14] * other[9] + m[15] * other[13],
			m[12] * other[2] + m[13] * other[6] + m[14] * other[10] + m[15] * other[14],
			m[12] * other[3] + m[13] * other[7] + m[14] * other[11] + m[15] * other[15]);
	}

	CMatrix4 &SetTranslation(const CVector3 &translation)
	{
		m[12] = translation.x;
		m[13] = translation.y;
		m[14] = translation.z;
		return *this;
	}

	CMatrix4 &BuildProjectionMatrixPerspectiveFovRH(float fieldOfViewRadians, float aspectRatio, float zNear, float zFar)
	{
		//const float h = static_cast<float>(1.0 / tan(fieldOfViewRadians * 0.5f));
		//assert(aspectRatio != 0.f);
		//const float w = static_cast<float>(h / aspectRatio);
		//assert(zNear != zFar);

		//m[0] = w;
		//m[1] = 0;
		//m[2] = 0;
		//m[3] = 0;

		//m[4] = 0;
		//m[5] = (float)h;
		//m[6] = 0;
		//m[7] = 0;

		//m[8] = 0;
		//m[9] = 0;
		//m[10] = (float)((zFar + zNear) / (zNear - zFar));
		//m[11] = -1;

		//m[12] = 0;
		//m[13] = 0;
		//m[14] = (float)(2.0f*zNear*zFar / (zNear - zFar));
		//m[15] = 0;

		float xmin, xmax, ymin, ymax; // Dimensions of near clipping plane

		// Do the Math for the near clipping plane
		ymax = zNear * float(tan(fieldOfViewRadians * 0.5f));
		ymin = -ymax;
		xmin = ymin * aspectRatio;
		xmax = -xmin;

		// Construct the projection matrix
		this->MakeIdentity();
		m[0] = (2.0f * zNear) / (xmax - xmin);
		m[5] = (2.0f * zNear) / (ymax - ymin);
		m[8] = (xmax + xmin) / (xmax - xmin);
		m[9] = (ymax + ymin) / (ymax - ymin);
		m[10] = -((zFar + zNear) / (zFar - zNear));
		m[11] = -1.0f;
		m[14] = -((2.0f * zFar * zNear) / (zFar - zNear));
		m[15] = 0.0f;

		return *this;
	}

	CMatrix4 &BuildProjectionMatrixPerspectiveFovLH(float fieldOfViewRadians, float aspectRatio, float zNear, float zFar)
	{
		const float h = static_cast<float>(1.0 / tan(fieldOfViewRadians * 0.5));
		assert(aspectRatio != 0.f);
		const float w = static_cast<float>(h / aspectRatio);
		assert(zNear != zFar);

		m[0] = w;
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (float)h;
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (float)(zFar / (zFar - zNear));
		m[11] = 1;

		m[12] = 0;
		m[13] = 0;
		m[14] = (float)(-zNear * zFar / (zFar - zNear));
		m[15] = 0;

		return *this;
	}

	CMatrix4 &BuildProjectionMatrixOrthoRH(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
	{
		assert(widthOfViewVolume != 0.f);
		assert(heightOfViewVolume != 0.f);
		assert(zNear != zFar);

		m[0] = (float)(2 / widthOfViewVolume);
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (float)(2 / heightOfViewVolume);
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (float)(2 / (zNear - zFar));
		m[11] = 0;

		m[12] = 0;
		m[13] = 0;
		m[14] = (float)((zNear + zFar) / (zNear - zFar));
		m[15] = 1;

		return *this;
	}

	CMatrix4 &BuildProjectionMatrixOrthoLH(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
	{
		assert(widthOfViewVolume != 0.f);
		assert(heightOfViewVolume != 0.f);
		assert(zNear != zFar);

		m[0] = (float)(2 / widthOfViewVolume);
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;

		m[4] = 0;
		m[5] = (float)(2 / heightOfViewVolume);
		m[6] = 0;
		m[7] = 0;

		m[8] = 0;
		m[9] = 0;
		m[10] = (float)(1 / (zFar - zNear));
		m[11] = 0;

		m[12] = 0;
		m[13] = 0;
		m[14] = (float)(zNear / (zNear - zFar));
		m[15] = 1;

		return *this;
	}

	CMatrix4 &BuildCameraLookAtMatrix(const CVector3 &position, const CVector3 &dir, const CVector3 &upVector)
	{
		CVector3 zaxis = -dir;
		zaxis.normalize();

		CVector3 xaxis = upVector.crossProduct(zaxis);
		xaxis.normalize();

		CVector3 yaxis = zaxis.crossProduct(xaxis);
		yaxis.normalize();

		m[0] = (float)xaxis.x;
		m[1] = (float)yaxis.x;
		m[2] = (float)zaxis.x;
		m[3] = 0;

		m[4] = (float)xaxis.y;
		m[5] = (float)yaxis.y;
		m[6] = (float)zaxis.y;
		m[7] = 0;

		m[8] = (float)xaxis.z;
		m[9] = (float)yaxis.z;
		m[10] = (float)zaxis.z;
		m[11] = 0;

		m[12] = (float)-xaxis.dotProduct(position);
		m[13] = (float)-yaxis.dotProduct(position);
		m[14] = (float)-zaxis.dotProduct(position);
		m[15] = 1;

		return *this;
	}
	CMatrix4 &BuildShadowMatrix(const CVector3 &light, const CPlane3 &plane, float point = 1.0f)
	{
	}

	CMatrix4 &SetInverseTranslation(const CVector3 &translation)
	{
		m[12] = -translation.x;
		m[13] = -translation.y;
		m[14] = -translation.z;
		return *this;
	}

	CMatrix4 &SetRotationRadiansRH(const float rotateX, const float rotateY, const float rotateZ)
	{
		const double cr = cos(rotateX);
		const double sr = sin(rotateX);
		const double cp = cos(rotateY);
		const double sp = sin(rotateY);
		const double cy = cos(rotateZ);
		const double sy = sin(rotateZ);

		m[0] = (float)(cp * cy);
		m[4] = (float)(-cp * sy);
		m[8] = (float)(sp);

		m[1] = (float)(sr * sp * cy + cr * sy);
		m[5] = (float)(-sr * sp * sy + cr * cy);
		m[9] = (float)(-sr * cp);

		m[2] = (float)(-cr * sp * cy + sr * sy);
		m[6] = (float)(cr * sp * sy + sr * cy);
		m[10] = (float)(cr * cp);

		return *this;
	}

	CMatrix4 &SetRotationRadiansLH(const float rotateX, const float rotateY, const float rotateZ)
	{
		const double cr = cos(rotateX);
		const double sr = sin(rotateX);
		const double cp = cos(rotateY);
		const double sp = sin(rotateY);
		const double cy = cos(rotateZ);
		const double sy = sin(rotateZ);

		m[0] = (float)(cp * cy);
		m[1] = (float)(cp * sy);
		m[2] = (float)(-sp);

		m[4] = (float)(sr * sp * cy - cr * sy);
		m[5] = (float)(sr * sp * sy + cr * cy);
		m[6] = (float)(sr * cp);

		m[8] = (float)(cr * sp * cy + sr * sy);
		m[9] = (float)(cr * sp * sy - sr * cy);
		m[10] = (float)(cr * cp);

		return *this;
	}

	CMatrix4 &SetRotationRadians(const float radian, const CVector3 &v)
	{
		float x = v.x;
		float y = v.y;
		float z = v.z;

		float fSin, fCos;
		fSin = sin(radian);
		fCos = cos(radian);

		m[0] = (x * x) * (1.0f - fCos) + fCos;
		m[1] = (x * y) * (1.0f - fCos) + (z * fSin);
		m[2] = (x * z) * (1.0f - fCos) - (y * fSin);
		m[3] = 0;

		m[4] = (y * x) * (1.0f - fCos) - (z * fSin);
		m[5] = (y * y) * (1.0f - fCos) + fCos;
		m[6] = (y * z) * (1.0f - fCos) + (x * fSin);
		m[7] = 0;

		m[8] = (z * x) * (1.0f - fCos) + (y * fSin);
		m[9] = (z * y) * (1.0f - fCos) - (x * fSin);
		m[10] = (z * z) * (1.0f - fCos) + fCos;
		m[11] = 0;

		m[12] = 0;
		m[13] = 0;
		m[14] = 0;
		m[15] = 1.0f;

		return *this;
	}

	inline CVector3 GetTranslation() const
	{
		return CVector3(m[12], m[13], m[14]);
	}

	inline bool GetInverse(CMatrix4 &out) const
	{
		/// Calculates the inverse of this Matrix
		/// The inverse is calculated using Cramers rule.
		/// If no inverse exists then 'false' is returned.

		const CMatrix4 &m = *this;

		float d = (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) -
				  (m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
				  (m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)) +
				  (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) -
				  (m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
				  (m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0));

		if (ISZERO(d))
			return false;

		d = 1 / d;

		out(0, 0) = d * (m(1, 1) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) +
						 m(1, 2) * (m(2, 3) * m(3, 1) - m(2, 1) * m(3, 3)) +
						 m(1, 3) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)));
		out(0, 1) = d * (m(2, 1) * (m(0, 2) * m(3, 3) - m(0, 3) * m(3, 2)) +
						 m(2, 2) * (m(0, 3) * m(3, 1) - m(0, 1) * m(3, 3)) +
						 m(2, 3) * (m(0, 1) * m(3, 2) - m(0, 2) * m(3, 1)));
		out(0, 2) = d * (m(3, 1) * (m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) +
						 m(3, 2) * (m(0, 3) * m(1, 1) - m(0, 1) * m(1, 3)) +
						 m(3, 3) * (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)));
		out(0, 3) = d * (m(0, 1) * (m(1, 3) * m(2, 2) - m(1, 2) * m(2, 3)) +
						 m(0, 2) * (m(1, 1) * m(2, 3) - m(1, 3) * m(2, 1)) +
						 m(0, 3) * (m(1, 2) * m(2, 1) - m(1, 1) * m(2, 2)));
		out(1, 0) = d * (m(1, 2) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) +
						 m(1, 3) * (m(2, 2) * m(3, 0) - m(2, 0) * m(3, 2)) +
						 m(1, 0) * (m(2, 3) * m(3, 2) - m(2, 2) * m(3, 3)));
		out(1, 1) = d * (m(2, 2) * (m(0, 0) * m(3, 3) - m(0, 3) * m(3, 0)) +
						 m(2, 3) * (m(0, 2) * m(3, 0) - m(0, 0) * m(3, 2)) +
						 m(2, 0) * (m(0, 3) * m(3, 2) - m(0, 2) * m(3, 3)));
		out(1, 2) = d * (m(3, 2) * (m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) +
						 m(3, 3) * (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) +
						 m(3, 0) * (m(0, 3) * m(1, 2) - m(0, 2) * m(1, 3)));
		out(1, 3) = d * (m(0, 2) * (m(1, 3) * m(2, 0) - m(1, 0) * m(2, 3)) +
						 m(0, 3) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
						 m(0, 0) * (m(1, 2) * m(2, 3) - m(1, 3) * m(2, 2)));
		out(2, 0) = d * (m(1, 3) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0)) +
						 m(1, 0) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
						 m(1, 1) * (m(2, 3) * m(3, 0) - m(2, 0) * m(3, 3)));
		out(2, 1) = d * (m(2, 3) * (m(0, 0) * m(3, 1) - m(0, 1) * m(3, 0)) +
						 m(2, 0) * (m(0, 1) * m(3, 3) - m(0, 3) * m(3, 1)) +
						 m(2, 1) * (m(0, 3) * m(3, 0) - m(0, 0) * m(3, 3)));
		out(2, 2) = d * (m(3, 3) * (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) +
						 m(3, 0) * (m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) +
						 m(3, 1) * (m(0, 3) * m(1, 0) - m(0, 0) * m(1, 3)));
		out(2, 3) = d * (m(0, 3) * (m(1, 1) * m(2, 0) - m(1, 0) * m(2, 1)) +
						 m(0, 0) * (m(1, 3) * m(2, 1) - m(1, 1) * m(2, 3)) +
						 m(0, 1) * (m(1, 0) * m(2, 3) - m(1, 3) * m(2, 0)));
		out(3, 0) = d * (m(1, 0) * (m(2, 2) * m(3, 1) - m(2, 1) * m(3, 2)) +
						 m(1, 1) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
						 m(1, 2) * (m(2, 1) * m(3, 0) - m(2, 0) * m(3, 1)));
		out(3, 1) = d * (m(2, 0) * (m(0, 2) * m(3, 1) - m(0, 1) * m(3, 2)) +
						 m(2, 1) * (m(0, 0) * m(3, 2) - m(0, 2) * m(3, 0)) +
						 m(2, 2) * (m(0, 1) * m(3, 0) - m(0, 0) * m(3, 1)));
		out(3, 2) = d * (m(3, 0) * (m(0, 2) * m(1, 1) - m(0, 1) * m(1, 2)) +
						 m(3, 1) * (m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) +
						 m(3, 2) * (m(0, 1) * m(1, 0) - m(0, 0) * m(1, 1)));
		out(3, 3) = d * (m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
						 m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
						 m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)));

		return true;
	}

	inline void GetTransposed(CMatrix4 &o) const
	{
		o[0] = m[0];
		o[1] = m[4];
		o[2] = m[8];
		o[3] = m[12];

		o[4] = m[1];
		o[5] = m[5];
		o[6] = m[9];
		o[7] = m[13];

		o[8] = m[2];
		o[9] = m[6];
		o[10] = m[10];
		o[11] = m[14];

		o[12] = m[3];
		o[13] = m[7];
		o[14] = m[11];
		o[15] = m[15];
	}

	inline void SetScale(const CVector3 &scale)
	{
		m[0] = scale.x;
		m[5] = scale.y;
		m[10] = scale.z;
	}

	inline void TransformVect(CVector3 &vect) const
	{
		float vector[3];

		vector[0] = vect.x * m[0] + vect.y * m[4] + vect.z * m[8] + m[12];
		vector[1] = vect.x * m[1] + vect.y * m[5] + vect.z * m[9] + m[13];
		vector[2] = vect.x * m[2] + vect.y * m[6] + vect.z * m[10] + m[14];

		vect.x = vector[0];
		vect.y = vector[1];
		vect.z = vector[2];
	}

	inline void TransformVect(CVector3 &out, const CVector3 &in) const
	{
		out.x = in.x * m[0] + in.y * m[4] + in.z * m[8] + m[12];
		out.y = in.x * m[1] + in.y * m[5] + in.z * m[9] + m[13];
		out.z = in.x * m[2] + in.y * m[6] + in.z * m[10] + m[14];
	}

	inline void TransformVect(float *out, const CVector3 &in) const
	{
		out[0] = in.x * m[0] + in.y * m[4] + in.z * m[8] + m[12];
		out[1] = in.x * m[1] + in.y * m[5] + in.z * m[9] + m[13];
		out[2] = in.x * m[2] + in.y * m[6] + in.z * m[10] + m[14];
		out[3] = in.x * m[3] + in.y * m[7] + in.z * m[11] + m[15];
	}

	inline void TransformPlane(CPlane3 &plane) const
	{
		CVector3 member;
		// Transform the plane member point, i.e. rotate, translate and scale it.
		TransformVect(member, plane.GetMemberPoint());

		// Transform the normal by the transposed inverse of the matrix
		CMatrix4 transposedInverse;
		if (!this->GetInverse(transposedInverse))
			memset(transposedInverse.m, 0, 16 * sizeof(float));
		else
			GetTransposed(transposedInverse);
		CVector3 normal = plane.m_vNormal;
		transposedInverse.TransformVect(normal);

		plane.SetPlane(member, normal);
	}

	float m[16];
};
} // namespace magic

#endif