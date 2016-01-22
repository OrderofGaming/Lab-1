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

#include "TTK/Shader.h"
#include "TTK/Vector4.h"
#include "TTK/Matrix4x4.h"
#include "GLEW/glew.h"

namespace TTK
{
	class TTK_API ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		// Initialization functions
		void attachShader(TTK::Shader shader);
		int linkProgram();

		// Usage functions
		void bind();
		void unbind();
		void sendUniform();

		// Functions to send uniforms to GPU from CPU

		// Sends a single integer value to GPU
		// Useful for assigning textures to samplers 
		void sendUniformInt(char* uniformName, int intVal);

		// Sends four floats stored in an array to GPU
		// Useful for sending vector4 to GPU
		void sendUniformVec4(char* uniformName, TTK::Vector4 vec4);

		// Sends a 4x4 matrix stored in an array to GPU
		// Must have to apply the MVP transform
		void sendUniformMat4(char* uniformName, TTK::Matrix4x4 mat4);

		void destroy();

	private:
		unsigned int handle;

		// All uniforms have a constant location
		// This function searches for the uniform name (as written in the shader)
		// and returns that location. If name is not found, it returns 0
		// Note: This is a pretty slow operation and you do not want to be
		// calling this every frame. Set up a system, such as a std::map which caches
		// the location and used the string name as a key
		int getUniformLocation(char* uniformName);
	};
};