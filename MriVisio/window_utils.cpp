#include "window_utils.h"

void window::create(const std::string& name)
{
	cvNamedWindow(name.c_str(), CV_WINDOW_AUTOSIZE);
}

void window::release_all()
{
	cvDestroyAllWindows();
}

bool window::show_with_exit_key(image_t img)
{
	cvShowImage(common_def::predefine_window_name, img);
	return cvWaitKey(0) == 27;
}

void window::create_with_trackbar(const std::string& name, int& trackbar_value, int trackbar_max_value, CvTrackbarCallback holder)
{
	cvCreateTrackbar(name.c_str(), common_def::predefine_window_name, &trackbar_value, trackbar_max_value, holder);
}

image_t window::show_scope(image_t img)
{
	if (img == NULL)
	{
		_out << "image is null" << _l;
		return NULL;
	}
		
	
	create(common_def::predefine_window_name);
	show_with_exit_key(img);
	release_all();

	return img;
}