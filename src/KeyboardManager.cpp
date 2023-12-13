#include "KeyboardManager.h"

KeyboardManager::KeyboardManager()
{
	for (int i = 0; i < KEYMAP_SIZE; i++) //Init keymap
	{
		keymap[i] = false;
	}
}

bool KeyboardManager::isPressed(uByte key)
{
	return keymap[key];
}