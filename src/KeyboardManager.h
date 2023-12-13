#pragma once
#include "../include/SDL.h"

#define KEYMAP_SIZE 0x10

using uByte = unsigned char;

class KeyboardManager
{
public:
	KeyboardManager();

	bool keymap[KEYMAP_SIZE];
	bool isPressed(uByte key);

};