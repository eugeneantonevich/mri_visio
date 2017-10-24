#pragma once

#include "definitions.h"

namespace actions
{
	contour find_brain_cortex(image_t image);

	contour find_brain_perimeter(image_t image);
}