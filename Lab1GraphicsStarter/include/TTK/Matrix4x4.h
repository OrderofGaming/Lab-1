//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
// This is the complete Matrix4x4 class
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////

#ifndef TTK_MATRIX44_H
#define TTK_MATRIX44_H

#ifdef TTK_EXPORTS
#define TTK_API __declspec(dllexport)
#else
#define TTK_API __declspec(dllimport)
#endif

#include "TTK/Matrix3x3.h"
#include "TTK/Vector3.h"
#include "TTK/Vector4.h"
#include "TTK/Quaternion.h"

namespace TTK
{
	class TTK_API Matrix4x4
	{
	public:

		// Creates an orthographic projection. 
		// Modern equivalent to glOrtho
		// Arguments:
		// left, right, bottom and top specify the size of the viewport
		// (left, bottom) specifies the bottom left of the view port in window space pixels
		// (right, top) specifies the top right
		// Sample use:
		// createOrthoProjection(0.0, windowWidth, 0.0, windowHeight)
		static Matrix4x4 createOrthoProjection(	float left, float right, 
												float bottom, float top, 
												float near = -1.0, float far = 1.0f);

		static Matrix4x4 createPerspectiveProjection( float fovRad, float aspect, float near, float far);

		// Creates the look at matrix, also known as the view transformation
		// Modern equivalent to gluLookAt
		// Arguments:
		// eye is the position of the camera
		// center is the point the camera is looking at
		// up is the global up axis, typically (0,1,0)
		static Matrix4x4 lookAt(TTK::Vector3 eye, TTK::Vector3 center, TTK::Vector3 up);

		Matrix4x4(); // Initializes to identity
		Matrix4x4(Matrix3x3 rotation, Vector3 translation, float scale);	// Creates homogeneous transformation matrix
		Matrix4x4(Matrix3x3 m33);

		Vector4 operator*(const Vector4 &b) const;
		Matrix4x4 operator*(const Matrix4x4 &b) const;

		Vector4 getRow0() const;
		Vector4 getRow1() const;
		Vector4 getRow2() const;
		Vector4 getRow3() const;

		void setRow0(TTK::Vector4 v);
		void setRow1(TTK::Vector4 v);
		void setRow2(TTK::Vector4 v);
		void setRow3(TTK::Vector4 v);

		// This is a column major matrix
		// The mapping from indices to cells in the matrix is as follows:
		/*
		0   4   8   12
		1   5   9   13
		2   6   10  14
		3   7   11  15
		*/
		// The formula for getting the index is:
		// row + (column*4)
		union
		{
			struct
			{
				Vector4 c0, c1, c2, c3;
			};
			float values[16];
		};
	};
}

#endif