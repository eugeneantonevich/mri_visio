
#include <string>

#include "image_utils.h"
#include "window_utils.h"
#include "common.h"
#include "actions.h"
#include "filters.h"

namespace iu = image_utils;

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
		{
			_out << "invalid arguments" << _l;
			return 1;
		}

		std::string input_directory = argv[1];
		_out << "read files from directory: " << input_directory << _l;
		files_t image_names = common::read_directory(input_directory);

		if (!image_names.size())
		{
			_out << "train images is empty " << _l;
			return 1;
		}

		for each (file_t img_name in image_names)
		{
			_out << "read image = " << img_name << _l;

			image_t img = image_utils::read_image(img_name);
			window::show_scope(img);

			/*
			window::show_scope(
				image_utils::contour_to_image(
					actions::find_brain_perimeter(img),
					image_utils::parameters::size(img),
					image_utils::parameters::depth(img),
					image_utils::parameters::channels(img))
			);			
			

			window::show_scope(
				image_utils::draw_contour_on_image(
					actions::find_brain_perimeter(img),
					img)
			);
			*/

			image_t cutter_image = 
				iu::cut_rect_from_image(
					img,
					image_utils::get_bounding_rect_image(actions::find_brain_perimeter(img)));

			contour_container contours = image_utils::find_countour(
				image_utils::smooth(
					image_utils::blackout(
						image_utils::laplace(
							image_utils::blackout(img, 2)
						),
						0.7),
					11,
					11
				),
				{ contour_filters::remove_noize }
			);

			window::show_scope(
				image_utils::contour_to_image(
					contours,
					image_utils::parameters::size(img),
					image_utils::parameters::depth(img),
					image_utils::parameters::channels(img)
				)
			);

			window::show_scope(
				image_utils::draw_contour_on_image(
					contours,
					img
				)
			);
		}
	}
	catch (std::exception& ex)
	{
		_out << "std ex = " << ex.what() << _l;
	}
	
	return 0;
}