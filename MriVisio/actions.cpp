#include "actions.h"
#include "image_utils.h"
#include "filters.h"

contour actions::find_brain_cortex(image_t image)
{
	image_t to_process = image_utils::blackout(image, 0.7);

	contour_container contours = image_utils::find_countour(
		to_process, 
		{
			contour_filters::cortex
		}
	);

	return image_utils::find_max_contour(contours);
}