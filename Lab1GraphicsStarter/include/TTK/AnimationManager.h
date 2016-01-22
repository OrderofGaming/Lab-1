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
#include "TTK/AnimationClip.h"
#include "TTK/GameObject.h"

#include <map>

namespace TTK
{
	class TTK_API AnimationManager
	{
	public:
		TTK::HTRLoader* loadAnimationHTR(std::string fileName, std::string friendlyName);

		// Returns a copy of an animation clip
		AnimationClip getAnimationClipByName(std::string friendlyName);

		std::map<std::string, GameObject> createGameObjectHierarchyFromHTR(TTK::HTRLoader* htr);

	private:
		std::map<std::string, TTK::HTRLoader> htrFiles;
		std::map<std::string, AnimationClip> animationClips;
	};
}