#pragma once

#include <string>
#include "TTK/Vector3.h"
#include "TTK/GraphicsUtils.h"

namespace TTK
{
	class TTK_API PointHandle
	{
	public:
		// Point size is in Pixels
		PointHandle(float _pointSize, TTK::Vector3 _position, std::string _label = "");

		void setPointSize(float size);

		// Does a simple radius based intersection test
		bool isInside(TTK::Vector3 p);

		void draw();


		TTK::Vector3 position;
		std::string label;

	private:
		float pointSize;
		float radiusSqrd;
	};
}