#include "chip8cpu.h"

inline void beep(void* arg)
{
	Beep(900, 50);
	_endthread();
}

chip8cpu::chip8cpu()
{
	resetCPU();
}

inline void chip8cpu::resetCPU()
{
	for (int i = 0; i < 16; i++)
	{
		V[i] = 0;
	}
	
	ST = 0;
	DT = 0;
	I = 0;
	PC = 0x200;
	SP = 0;
}

void chip8cpu::updateTimers(unsigned int FPS)
{
	int delay = FPS / 60;

	if (ST > 0)
	{
		_beginthread(beep, 0, NULL);
		if (ST - delay < 0)
		{
			ST = 0;
		}
		else {
			ST -= delay;
		}
	}

	if (DT > 0)
	{
		if (DT - delay < 0)
		{
			DT = 0;
		}
		else {
			DT -= delay;
		}
	}
}