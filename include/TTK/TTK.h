//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
// This is the main TTK header. This header simply includes all the other
// TTK headers.
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////

#ifndef TTK_H
#define TTK_H

#define GLEW_STATIC
#include "GLEW/glew.h"

#include "TTK/GraphicsUtils.h"
#include "TTK/Vector3.h"
#include "TTK/Matrix3x3.h"
#include "TTK/Matrix4x4.h"
#include "TTK/Texture2D.h"
#include "TTK/Quaternion.h"
#include "TTK/Camera.h"
#include "TTK/Particle.h"
#include "TTK/ParticleEmitter.h"
#include "TTK/HTRLoader.h"
#include "TTK/PointHandle.h"
#include "TTK/AnimationClip.h"
#include "TTK/AnimationManager.h"
#include "TTK/AnimationMath.h"
#include "TTK/GameObject.h"
#include "TTK/KeyframeController.h"
#include "TTK/JointTypes.h"
#include "TTK/IO.h"
#include "TTK/Shader.h"
#include "TTK/ShaderProgram.h"

#ifdef TTK_EXPORTS
#define TTK_API __declspec(dllexport)
#else
#define TTK_API __declspec(dllimport)
#endif

// Useful conversions
static const float degToRad = 3.14159f / 180.0f;
static const float radToDeg = 180.0f / 3.14159f;

namespace TTK
{
	TTK_API void InitializeTTK();
}

#endif
