#pragma once
#include "definitions.h"

namespace window
{
	void create(const std::string& name);
	void release_all();
	bool show_with_exit_key(image_t img);
	image_t show_scope(image_t img);
	void create_with_trackbar(const std::string& name, int& trackbar_value, int trackbar_max_value, CvTrackbarCallback holder);
}