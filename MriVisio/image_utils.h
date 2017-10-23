#pragma once

#include "definitions.h"

namespace image_utils
{
	namespace parameters
	{
		int depth(image_t image);
		CvSize size(image_t image);
		int channels(image_t image);
	}

	image_t blackout(image_t image);
	image_t clone(image_t image);
	image_t canny(image_t img, int size = 3);
	image_t create_by_template(image_t image);
	image_t create(CvSize size, int depth, int nChannels);
	image_t lightening(image_t image);
	image_t blackout(image_t image, float factor = 1.0);
	image_t laplace(image_t image, int aperture = 3);
	image_t sobel(image_t image, int xorder = 1, int xorder_max = 2, int yorder = 1, int yorder_max = 2, int aperture = 3);
	image_t to_8bit(image_t image);

	image_t smooth(image_t image);

	image_t threshold(image_t image, int min = 127, int max= 255);

	contour_container find_countour(image_t image, contour_filter_container filters = contour_filter_container());

	image_t contour_to_image(contour_container cont, CvSize size, int depth, int channels);

	image_t contour_to_image(contour cont, CvSize size, int depth, int channels);

	contour find_max_contour(contour_container cont);
}