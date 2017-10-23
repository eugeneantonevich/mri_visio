#include "common.h"

images_container common::read_directory(const std::string& path)
{
	images_container images(new std::list<image_t>());

	for (auto file : std::experimental::filesystem::directory_iterator(path.c_str()))
	{
		images->push_back(cvLoadImage(file.path().u8string().c_str()));
	}
	return images;
}


