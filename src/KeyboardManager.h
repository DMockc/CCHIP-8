#pragma once
#include "../include/SDL.h"

#define KEYMAP_SIZE 0x10

using uByte = unsigned char;

namespace Keyboard
{
	extern bool keymap[KEYMAP_SIZE];
	bool isPressed(uByte key);
	bool isReleased(SDL_Event& event, uByte key);
	void updateKeymap(SDL_Event& event, unsigned int& FPS);
}; //namespace: Keyboard