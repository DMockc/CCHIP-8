#include "fileManager.h"

bool checkExtension(const char* file_path)
{
	std::string filename = file_path;
	std::string::size_type idx;
	
	idx = filename.rfind('.');

	if (!(idx != std::string::npos && filename.substr(idx) == ".ch8"))
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::pair<char*, size_t> loadFileInBuffer(std::ifstream& file)
{
	if (!file.is_open())
	{
		return std::make_pair(nullptr, NULL);
	}

	std::streampos file_size = file.tellg();
	char* fileContent = new char[file_size];

	file.seekg(0, std::ios::beg);
	file.read(fileContent, file_size);
	file.close();

	return std::make_pair(fileContent, static_cast<size_t>(file_size));
}