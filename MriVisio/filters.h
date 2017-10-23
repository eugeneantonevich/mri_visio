#pragma once
#include "definitions.h"

namespace contour_filters
{
	extern std::function<bool(contour)> empty;
	extern std::function<bool(contour)> cortex;
}