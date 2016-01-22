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

#include "TTK/HTRLoader.h"
#include <string>

namespace TTK
{
	class TTK_API AnimationClip
	{
	public:
		AnimationClip();

		void update(float dt);

		bool doesLoop;
		bool playing;

		bool cutsceneMode;

		//private:
		TTK::HTRLoader* htrData;
		int currentFrame;
	};
}