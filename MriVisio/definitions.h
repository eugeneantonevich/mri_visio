#pragma once

#include "opencv2\highgui\highgui.hpp"
#include <memory>
#include <iostream>
#include <filesystem>

#include "contour.h"

#define _out std::cout
#define _in std::cin
#define _l std::endl

namespace common_def
{
	extern char predefine_window_name[];
}

namespace fs = std::experimental::filesystem;

typedef IplImage* image_t;
typedef std::list<image_t> images_container;

typedef std::string			file_t;
typedef std::list<file_t>	files_t;
