//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
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

#include "TTK/Vector3.h"
#include "TTK/Vector4.h"
#include "TTK/GraphicsUtils.h"

namespace TTK
{
	class TTK_API Particle
	{
	public:
		Particle();

		void update(float dt);
		void draw();
		void setInitialLife(float _life);
		bool isAlive();

		// Initial force modes: point, circle, random

		TTK::Vector3 velocity;
		TTK::Vector3 position;
		TTK::Vector3 acceleration;

		float mass;

		float scale;

		// Visual properties
		TTK::Vector4 colour;

		float life; // in seconds
		float initialLife; // useful for lerping
	};
}