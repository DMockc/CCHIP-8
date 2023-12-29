#pragma once

#include <fstream>
#include <iostream>

bool checkExtension(const char* file_path);
std::pair<char*, size_t> loadFileInBuffer(std::ifstream& file);