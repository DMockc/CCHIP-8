#pragma once
#include <fstream>

bool checkExtension(const char* filename);

/* First value is the buffer pointer and second value is the size of the pointer */
[[nodiscard]] std::pair<char*, int> loadFileInBuffer(std::ifstream& file);