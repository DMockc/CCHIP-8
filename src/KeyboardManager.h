#pragma once
#include "../include/SDL.h"

#define KEYMAP_SIZE 0x10

using uByte = unsigned char;

namespace Keyboard
{
	extern bool keymap[KEYMAP_SIZE];
	bool isPressed(uByte key);
	void updateKeymap(SDL_Event& event, unsigned int& FPS);
}; //namespace: Keyboard