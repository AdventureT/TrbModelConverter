#pragma once
#include <stdlib.h>
#include <math.h>
#include <xlocale>

// Rotation Orders, Matrix Calculated in Reversed Order
#define		XYZ		0
#define		XZY		1
#define		YZX		2
#define		YXZ		3
#define		ZXY		4
#define		ZYX		5

// Linear storage of matrix tuple
#define		ColMajor	0
#define		RowMajor	1

/* Function Declarations */
void Quat2EulerAngles(float q[4], double YawPitchRoll[3]);
void Matrix33ToRS(float* Mat33, double R[3], double S[3], int RotationOrder);
void Matrix344ToTRS(float* Mat344, double T[3], double R[3], double S[3], int RotationOrder);
void TransposeMatrix33(float* Mat33);
void TransposeMatrix44(float* Mat44);
void inv(float dest[16], const float Src[16], int storageMethod);
void mul(float dest[16], const float src1[16], const float src2[16], int storageMethod);
/* Functions Definitions */

/* Quaternion to Euler Rotation Convertion
 q[4]: Quaternion Rotaion (x,y,z,w)
 YawPitchRoll[3]: Euler Rotation
*/
void Quat2EulerAngles(float q[4], double YawPitchRoll[3])		// Store the Euler angles in degrees
{
	double sqx, sqy, sqz, sqw, unit, test;
	double PI = 3.1415926535897932;

	sqx = q[0] * q[0];
	sqy = q[1] * q[1];
	sqz = q[2] * q[2];
	sqw = q[3] * q[3];

	// If quaternion is normalised the unit is one, otherwise it is the correction factor
	unit = sqx + sqy + sqz + sqw;
	test = -(q[0] * q[2] + q[1] * q[3]);

	if (test > 0.4999 * unit) // Singularity at north pole
	{
		YawPitchRoll[0] = -2.0 * atan2(q[0], q[3]);		// Yaw
		YawPitchRoll[1] = PI * 0.5;						// Pitch
		YawPitchRoll[2] = 0.0;							// Roll
	}
	else if (test < -0.4999 * unit) // Singularity at south pole
	{
		YawPitchRoll[0] = -2.0 * atan2(q[0], q[3]);		// Yaw
		YawPitchRoll[1] = -PI * 0.5;					// Pitch
		YawPitchRoll[2] = 0.0;							// Roll
	}
	else
	{
		YawPitchRoll[0] = atan2(2.0 * (q[1] * q[2] - q[0] * q[3]), -sqx - sqy + sqz + sqw);		// Yaw 
		YawPitchRoll[1] = asin(2.0 * test / unit);												// Pitch 
		YawPitchRoll[2] = atan2(2.0 * (q[0] * q[1] - q[2] * q[3]), sqx - sqy - sqz + sqw);		// Roll 
	}

	for (int i = 0; i < 3; i++)
	{
		YawPitchRoll[i] *= 180.0 / PI;
		if (YawPitchRoll[i] > 180.0)
			YawPitchRoll[i] -= 360.0;
		else if (YawPitchRoll[i] < -180.0)
			YawPitchRoll[i] += 360;
	}
}

/* Extract Euler Rotation and Scaling Vectors from a 3x3 Row-major Matrix
Default Rotation Order: XYZ (R = Rz * Ry * Rx, where R, Rx, Ry and Rz are all 3x3 matrices)
*/
void Matrix33ToRS(float* Mat33, double R[3], double S[3], int RotationOrder)
{
	float Rot[9];
	double PI = 3.1415926535897932;

	S[0] = sqrt((double)(Mat33[0] * Mat33[0] + Mat33[1] * Mat33[1] + Mat33[2] * Mat33[2]));
	S[1] = sqrt((double)(Mat33[3] * Mat33[3] + Mat33[4] * Mat33[4] + Mat33[5] * Mat33[5]));
	S[2] = sqrt((double)(Mat33[6] * Mat33[6] + Mat33[7] * Mat33[7] + Mat33[8] * Mat33[8]));

	// Create a copy of the 3x3 rotation matrix
	memcpy_s(Rot, sizeof(float) * 9, Mat33, sizeof(float) * 9);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Rot[i + j] /= (float)S[i];
	switch (RotationOrder)
	{
	default:
	case XYZ:
		R[0] = atan2((double)Rot[7], (double)Rot[8]);
		R[1] = atan2(-(double)Rot[6], (double)Rot[7] * sin(R[0]) + (double)Rot[8] * cos(R[0]));
		R[2] = atan2((double)Rot[3], (double)Rot[0]);
		break;
	case XZY:
		R[0] = atan2(-(double)Rot[5], (double)Rot[4]);
		R[1] = atan2(-(double)Rot[6], (double)Rot[0]);
		R[2] = atan2((double)Rot[3], (double)Rot[0] * cos(R[1]) - (double)Rot[6] * sin(R[1]));
		break;
	case YZX:
		R[0] = atan2((double)Rot[7], (double)Rot[4]);
		R[1] = atan2((double)Rot[2], (double)Rot[0]);
		R[2] = atan2(-(double)Rot[1], (double)Rot[0] * cos(R[1]) + (double)Rot[2] * sin(R[1]));
		break;
	case YXZ:
		R[2] = atan2(-(double)Rot[1], (double)Rot[4]);
		R[1] = atan2(-(double)Rot[6], (double)Rot[8]);
		R[0] = atan2((double)Rot[7], (double)Rot[4] * cos(R[2]) - (double)Rot[1] * sin(R[2]));
		break;
	case ZXY:
		R[2] = atan2((double)Rot[3], (double)Rot[4]);
		R[1] = atan2((double)Rot[2], (double)Rot[8]);
		R[0] = atan2(-(double)Rot[5], (double)Rot[3] * sin(R[2]) + (double)Rot[4] * cos(R[2]));
		break;
	case ZYX:
		R[0] = atan2(-(double)Rot[5], (double)Rot[8]);
		R[1] = atan2((double)Rot[2], (double)Rot[8] * cos(R[0]) - (double)Rot[5] * sin(R[0]));
		R[2] = atan2(-(double)Rot[1], (double)Rot[0]);
		break;
	}
	for (int i = 0; i < 3; i++)
		R[i] *= 180.0 / PI;
}

/* Extract Translation, Euler Rotation and Scaling Vectors from a 4x4/3x4 Row-major Matrix
Assume Mat4x4 = T * S * R, where T, R, S are all 4x4 matrices
*/
void Matrix344ToTRS(float* Mat344, double T[3], double R[3], double S[3], int RotationOrder)
{
	float Rot[9];

	T[0] = Mat344[3];
	T[1] = Mat344[7];
	T[2] = Mat344[11];

	// Convert 4x matrix to 3x3 rotation matrix
	memcpy(Rot, Mat344, sizeof(float) * 3);
	memcpy(Rot + 3, Mat344 + 4, sizeof(float) * 3);
	memcpy(Rot + 6, Mat344 + 8, sizeof(float) * 3);

	Matrix33ToRS(Rot, R, S, RotationOrder);
}

/* Convert a 3x3 column-major rotation matrix tuple to row-major tuple and vice versa */
void TransposeMatrix33(float* Mat33)
{
	int temp[9];
	int* pInt;

	pInt = (int*)Mat33;
	temp[0] = pInt[0];
	temp[1] = pInt[3];
	temp[2] = pInt[6];
	temp[3] = pInt[1];
	temp[4] = pInt[4];
	temp[5] = pInt[7];
	temp[6] = pInt[2];
	temp[7] = pInt[5];
	temp[8] = pInt[8];

	memcpy_s(pInt, 36, temp, 36);
}

/* Convert a 4x4 column-major matrix tuple to row-major tuple and vice versa */
void TransposeMatrix44(float* Mat44)
{
	int temp[16];
	int* pInt;

	pInt = (int*)Mat44;
	temp[0] = pInt[0];
	temp[1] = pInt[4];
	temp[2] = pInt[8];
	temp[3] = pInt[12];
	temp[4] = pInt[1];
	temp[5] = pInt[5];
	temp[6] = pInt[9];
	temp[7] = pInt[13];
	temp[8] = pInt[2];
	temp[9] = pInt[6];
	temp[10] = pInt[10];
	temp[11] = pInt[14];
	temp[12] = pInt[3];
	temp[13] = pInt[7];
	temp[14] = pInt[11];
	temp[15] = pInt[15];

	memcpy_s(pInt, 0x40, temp, 0x40);
}

/* Fast method for calculating the inverse of a 4x4 row/column-major matrix tuple */
void inv(float dest[16], const float Src[16], int storageMethod)
{
	float result[16];
	float Rot[9];
	float Scl[3];
	int i;
	int i0;
	int i1;
	static const signed char iv0[4] = { 0, 0, 0, 1 };

	// Rot = transpose(Src.Rot)
	for (i0 = 0; i0 < 3; i0++)
	{
		for (i1 = 0; i1 < 3; i1++)
		{
			Rot[i1 + 3 * i0] = Src[(i1 << 2) + i0];
		}
	}

	if (storageMethod == 1) // row-major
	{
		// obtain scaling
		i = 0;
		for (i0 = 0; i0 < 3; i0++)
		{
			Scl[i0] = 0.0f;
			for (i1 = 0; i1 < 3; i1++)
			{
				Scl[i0] += Rot[i] * Rot[i];
				i++;
			}
		}

		// calculate rotation and translation
		for (i0 = 0; i0 < 3; i0++)
		{
			i = (i0 << 2) + 3;
			result[i] = 0.0f;
			for (i1 = 0; i1 < 3; i1++)
			{
				result[(i0 << 2) + i1] = Rot[i0 * 3 + i1];
				result[i] += (-Rot[i0 * 3 + i1] * Src[(i1 << 2) + 3]);
			}
		}

		for (i0 = 0; i0 < 4; i0++)
		{
			result[12 + i0] = iv0[i0];
		}

		for (i = 0; i < 3; i++)
		{
			for (i0 = 0; i0 < 4; i0++)
			{
				result[(i << 2) + i0] /= Scl[i];
			}
		}
	}
	else // column-major
	{
		// obtain scaling
		i = 0;
		for (i0 = 0; i0 < 3; i0++)
		{
			Scl[i0] = 0.0f;
			for (i1 = 0; i1 < 3; i1++)
			{
				Scl[i0] += Src[i] * Src[i];
				i++;
			}
			i++;
		}

		// calculate rotation and translation
		for (i = 0; i < 3; i++)
		{
			result[12 + i] = 0.0f;
			for (i0 = 0; i0 < 3; i0++)
			{
				result[(i << 2) + i0] = Rot[i * 3 + i0];
				result[12 + i] += (-Src[12 + i0] * Rot[i0 * 3 + i]);
			}

			result[(i << 2) + 3] = 0.0f;
		}
		result[15] = 1.0f;

		for (i = 0; i < 3; i++)
		{
			for (i0 = 0; i0 < 4; i0++)
			{
				result[(i0 << 2) + i] /= Scl[i];
			}
		}
	}

	memcpy(dest, result, 0x40);
}

/* Calculate (src1 * src2) and maintain the given storage method(ColMajor/RowMajor) */
void mul(float dest[16], const float src1[16], const float src2[16], int storageMethod)
{
	float result[16];
	const float* M1;
	const float* M2;
	int idx;
	int i1;
	int i2;
	int i3;

	if (storageMethod) // RowMajor
	{
		M1 = src1;
		M2 = src2;
	}
	else // ColMajor
	{
		M1 = src2;
		M2 = src1;
	}

	for (i1 = 0; i1 < 4; i1++)
	{
		for (i2 = 0; i2 < 4; i2++)
		{
			idx = (i1 * 4) + i2;
			result[idx] = 0.0f;
			for (i3 = 0; i3 < 4; i3++)
			{
				result[idx] += M1[(i1 * 4) + i3] * M2[(i3 * 4) + i2];
			}
		}
	}
	memcpy(dest, result, 0x40);
}