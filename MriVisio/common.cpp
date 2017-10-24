#include "common.h"

files_t common::read_directory(const std::string& path)
{
	files_t fs;
	for (auto f : std::experimental::filesystem::directory_iterator(path.c_str()))
	{
		fs.push_back(f.path().u8string().c_str());
	}
	return fs;

}

std::string common::append_prefix(const std::string& full_name, const std::string& prefix)
{
	std::experimental::filesystem::path name = std::experimental::filesystem::path(full_name);
	name.replace_filename(std::string("cortex_").append(name.filename().u8string()));
	return name.u8string();
}