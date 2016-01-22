#pragma once

#include <fstream>
#include <string>

#include "TTK/TTK.h"

namespace TTK
{
	namespace IO
	{
		TTK_API const char* loadFile(std::string fileName);
	}
}