#pragma once

#include "definitions.h"

namespace common
{	
	std::string append_prefix(const std::string& full_name, const std::string& prefix);

	files_t read_directory(const std::string& path);
}


