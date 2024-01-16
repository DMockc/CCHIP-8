#include "fileManager.h"

bool checkExtension(const char* file_path)
{
	std::string filename = file_path;
	std::string::size_type dotLocation;
	
	dotLocation = filename.rfind('.');

	if (dotLocation != std::string::npos && filename.substr(dotLocation) == ".ch8")
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::pair<char*, size_t> loadFileInBuffer(std::ifstream& file)
{
	if (!file.is_open())
	{
		file.close();
		return std::make_pair(nullptr, NULL);
	}

	std::streampos file_size = file.tellg();
	char* fileContent = new char[file_size];

	file.seekg(0, std::ios::beg);
	file.read(fileContent, file_size);
	file.close();

	return std::make_pair(fileContent, static_cast<size_t>(file_size));
}