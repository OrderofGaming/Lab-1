//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
// This header contains utility functions for drawing.
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////

#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#ifdef TTK_EXPORTS
#define TTK_API __declspec(dllexport)
#else
#define TTK_API __declspec(dllimport)
#endif

#include "Matrix4x4.h"
#include <string>

namespace TTK
{
	class TTK_API Graphics
	{
	public:
		// Description:
		// Draws a cube at the specified position in world space.
		// TTK_API static void DrawCube(Vector3 position, float size);

		// Description:
		// Draws text at the specified position on the screen. Make sure
		// you call SetCameraMode2D before you try drawing any text.
		// Arguments:
		// posX, posY are to be specified in pixels. 0, 0 is the top left
		// corner of the window.
		static void DrawText2D(std::string text, int posX, int posY);

		// Description:
		// Draws a line from p0 to p1
		// lineWidth is the width of the line in pixels
		// colour is the colour of the line (r,g,b)
		static void DrawLine(float* p0, float* p1, float lineWidth = 1.0f, float *colour = nullptr);

		static void DrawVector(float* origin, float* vectorToDraw, float lineWidth = 1.0f, float *colour = nullptr);

		// Description:
		// Draws point at specified position.
		// Arguments:
		// p0 is an array of 3 floats representing position
		// pointSize lets you specify the size of the point, in pixels (p0 is center of point)
		static void DrawPoint(float *p0, float pointSize, float *colour = nullptr);

		// Description:
		// Draws a cube at position p0 with the specified size
		// This will set the camera mode to model view, push matrix apply the
		// cube's transformation and pop matrix
		// Colour is expected to be an array of four floats (rgba)
		static void DrawCube(float *p0, float size = 1.0f, float *colour = nullptr);
		
		static void DrawSphere(TTK::Matrix4x4 matrix4x4, TTK::Vector4 colour = TTK::Vector4(), float scale = 1.0f, int slices = 8, int stacks = 4);

		//static void DrawPrism(TTK::Matrix4x4, TTK::Vector3 colour, float scale);

		// Description:
		// Draws teabro
		static void DrawTeapot(float *p0, float size = 1.0f, float *colour = nullptr);

		// Description:
		// Draws a grid on the XZ plane. The size of each cell in the grid is one unit.
		static void DrawGrid();

		// Description:
		// Clears the current projection matrix and then resets it
		// to an orthographic projection.
		// Note: This function uses deprecated opengl functions.
		// See TTK::Camera for a modern implementation
		static void SetCameraMode2D(int windowWidth, int windowHeight);

		// Description:
		// Clears the current projection matrix and then resets it
		// to an perspective projection with a field of view (FOV) of 60 degrees.
		// Note: This function uses deprecated opengl functions.
		// See TTK::Camera for a modern implementation
		static void SetCameraMode3D(int windowWidth, int windowHeight);

		// Description:
		// Sets the colour of the screen after ClearScreen() has been called.
		static void SetBackgroundColour(float r, float g, float b);

		// Description:
		// Removes all content from the screen. This should be called at
		// the beginning of every draw function.
		static void ClearScreen();
	};
}

#endif