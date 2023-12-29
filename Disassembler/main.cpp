#include "fileReader.h"
#include "Disassembler.h"

int main(int argc, char** argv)
{
	argc = 2;
	const char* path = "";

	if (argc != 2)
	{
		std::cout << "Usage: ./disassembler.exe <filename>.ch8";
		exit(0);
	}

	checkExtension(path);

	std::ifstream file(path, std::ios::binary | std::ios::ate);

	std::pair<char*, size_t> fileContent = loadFileInBuffer(file);

	Disassembler::disassembly(fileContent.first, fileContent.second);

	delete[] fileContent.first;

	return 0;
}
