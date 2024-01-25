#include "KeyboardManager.h"

namespace Keyboard {

	bool keymap[KEYMAP_SIZE];

	bool Keyboard::isPressed(uByte key)
	{
		return keymap[key];
	}

	bool Keyboard::isReleased(SDL_Event& event, uByte key)
	{

		switch (event.type)
		{
		case SDL_KEYUP:

			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				if (key == 0x1)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_2:
				if (key == 0x2)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_3:
				if (key == 0x3)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_4:
				if (key == 0xC)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_q:
				if (key == 0x4)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_w:
				if (key == 0x5)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_e:
				if (key == 0x6)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_r:
				if (key == 0xD)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_a:
				if (key == 0x7)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_s:
				if (key == 0x8)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_d:
				if (key == 0x9)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_f:
				if (key == 0xE)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_z:
				if (key == 0xA)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_x:
				if (key == 0x0)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_c:
				if (key == 0xB)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			case SDLK_v:
				if (key == 0xF)
				{
					return true;
				}
				else
				{
					return false;
				}
				break;

			default:
				return false;
				break;
			}

			return false;
			break;
		}
		return false;
	}

	void updateKeymap(SDL_Event& event, unsigned int& FPS, std::string& text, Uint8& alpha)
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
						text = "Speed x2";
					}
					else
					{
						FPS >>= 1;
						speedUp = false;
						text = "Speed x1";
					}
					alpha = 255;
				}

				break;

			case SDLK_i: //Slow down
				if (!speedUp) {
					if (!slowDown) {
						FPS >>= 1;
						slowDown = true;
						text = "Speed x0.5";
					}
					else
					{
						FPS <<= 1;
						slowDown = false;
						text = "Speed x1";
					}
					alpha = 255;
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