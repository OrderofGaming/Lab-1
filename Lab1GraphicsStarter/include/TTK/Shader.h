//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////


#pragma once

#ifdef TTK_EXPORTS
#define TTK_API __declspec(dllexport)
#else
#define TTK_API __declspec(dllimport)
#endif

#include <string>

#define GLEW_STATIC
#include "GLEW/glew.h"

namespace TTK
{
	class TTK_API Shader
	{
	private:
		unsigned int handle;
		GLenum shaderType;

	public:
		Shader();
		~Shader();

		// Returns shader handle
		unsigned int loadShaderFromFile(std::string fileName, GLenum type);

		unsigned int getHandle() { return handle; }

		void destroy();
	};
};