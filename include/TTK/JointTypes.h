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

#include "TTK/Vector3.h"
#include "TTK/Quaternion.h"
#include <vector>

namespace TTK
{
	enum TTK_API RotationOrder
	{
		// The two we care about
		XYZ = 0,
		ZYX,


		XZY,
		YXZ,
		YZX

		// ... 
	};
	
	struct TTK_API JointDescriptor
	{
		std::string jointName;		// Name of joint
		std::string jointParent;	// Name of joint's parent
		TTK::Vector3	jointBasePosition;	// Position of joint at frame 0
		TTK::Quaternion jointBaseRotation;	// Rotation of joint at frame 0
		float	boneLength;
		// If scale was exported (remember dataType member) we would want to store that too

		std::vector<Vector3>	jointPositions;		// Joint point for each frame (should all be zero except for root)
		std::vector<TTK::Quaternion> jointRotations;	// Joint rotations for each frame 
		std::vector<float> jointScales;
	};
}