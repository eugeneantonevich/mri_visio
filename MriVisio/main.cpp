
#include <string>

#include "image_utils.h"
#include "window_utils.h"
#include "common.h"
#include "actions.h"


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
		images_container images = common::read_directory(input_directory);

		if (!images->size())
		{
			_out << "train images is empty " << _l;
			return 1;
		}

		for each (auto img in *images)
		{
			window::show_scope(img);

			window::show_scope(
				image_utils::contour_to_image(actions::find_brain_cortex(img),
					image_utils::parameters::size(img),
					image_utils::parameters::depth(img),
					image_utils::parameters::channels(img))
			);
		}
	}
	catch (std::exception& ex)
	{
		_out << "std ex = " << ex.what() << _l;
	}
	return 0;
}