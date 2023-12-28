#include "KeyboardManager.h"

namespace Keyboard {

	bool keymap[KEYMAP_SIZE];

	bool Keyboard::isPressed(uByte key)
	{
		return keymap[key];
	}

	void updateKeymap(SDL_Event& event, unsigned int& FPS)
	{
		static bool speedUp = false;
		static bool slowDown = false;

		switch (event.type)
		{
#pragma region KEYDOWN
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym)
			{

			case SDLK_o: //Speed up
				if (!slowDown) {
					if (!speedUp) {
						FPS <<= 1;
						speedUp = true;
					}
					else
					{
						FPS >>= 1;
						speedUp = false;
					}
				}

				break;

			case SDLK_i: //Slow down
				if (!speedUp) {
					if (!slowDown) {
						FPS >>= 1;
						slowDown = true;
					}
					else
					{
						FPS <<= 1;
						slowDown = false;
					}
				}

				break;



			case SDLK_1:
				Keyboard::keymap[0x01] = true;
				break;

			case SDLK_2:
				Keyboard::keymap[0x02] = true;
				break;

			case SDLK_3:
				Keyboard::keymap[0x03] = true;
				break;

			case SDLK_4:
				Keyboard::keymap[0x0C] = true;
				break;

			case SDLK_q:
				Keyboard::keymap[0x04] = true;
				break;

			case SDLK_w:
				Keyboard::keymap[0x05] = true;
				break;

			case SDLK_e:
				Keyboard::keymap[0x06] = true;
				break;

			case SDLK_r:
				Keyboard::keymap[0x0D] = true;
				break;

			case SDLK_a:
				Keyboard::keymap[0x07] = true;
				break;

			case SDLK_s:
				Keyboard::keymap[0x08] = true;
				break;

			case SDLK_d:
				Keyboard::keymap[0x09] = true;
				break;

			case SDLK_f:
				Keyboard::keymap[0x0E] = true;
				break;

			case SDLK_z:
				Keyboard::keymap[0x0A] = true;
				break;

			case SDLK_x:
				Keyboard::keymap[0x00] = true;
				break;

			case SDLK_c:
				Keyboard::keymap[0x0B] = true;
				break;

			case SDLK_v:
				Keyboard::keymap[0x0F] = true;
				break;

			default:
				break;
			}

			break;
#pragma endregion
#pragma region KEYUP
		case SDL_KEYUP:

			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				Keyboard::keymap[0x01] = false;
				break;

			case SDLK_2:
				Keyboard::keymap[0x02] = false;
				break;

			case SDLK_3:
				Keyboard::keymap[0x03] = false;
				break;

			case SDLK_4:
				Keyboard::keymap[0x0C] = false;
				break;

			case SDLK_q:
				Keyboard::keymap[0x04] = false;
				break;

			case SDLK_w:
				Keyboard::keymap[0x05] = false;
				break;

			case SDLK_e:
				Keyboard::keymap[0x06] = false;
				break;

			case SDLK_r:
				Keyboard::keymap[0x0D] = false;
				break;

			case SDLK_a:
				Keyboard::keymap[0x07] = false;
				break;

			case SDLK_s:
				Keyboard::keymap[0x08] = false;
				break;

			case SDLK_d:
				Keyboard::keymap[0x09] = false;
				break;

			case SDLK_f:
				Keyboard::keymap[0x0E] = false;
				break;

			case SDLK_z:
				Keyboard::keymap[0x0A] = false;
				break;

			case SDLK_x:
				Keyboard::keymap[0x00] = false;
				break;

			case SDLK_c:
				Keyboard::keymap[0x0B] = false;
				break;

			case SDLK_v:
				Keyboard::keymap[0x0F] = false;
				break;

			default:
				break;
			}

			break;
		}
#pragma endregion
	}
}; //namespace: Keyboard