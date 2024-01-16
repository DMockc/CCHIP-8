#pragma once

#include "../include/SDL.h" //_begin and _end thread
#ifdef _WIN32
#include <Windows.h>
#endif

#define BITS_IN_A_BYTE 8
using uByte = unsigned char;
using uWord = unsigned short;

struct chip8cpu
{
	chip8cpu();

	inline void resetCPU();

	void updateTimers(unsigned int FPS);

	/* Registers
		* V0 - VE: General-purpose 8-bit registers
		* VF: 8-bit flag register, constains Carry Flag (additions) and Borrow Flags (subtractions)
		
		* ST (Sound Timer): 8-bit register, is decremented with a frequency of 60Hz when its value is grater than zero. Additionally, when `ST > 0` the system
		*	sounds the buzzer to produce a beep.
		 
		* DT (Delay Timer): 8-bit register, is decremented with a frequency of 60Hz when its value is greater than zero
		
		* I: 16-bit register, contains Memory Addresses
		
		* PC (Program Counter): 16-bit register, contains the memory address of the current instruction
		
		* SP (Stack Pointer):
	*/

	uByte V[16]; //V0, V1, V2, ..., VF
	uByte ST;
	uByte DT;
	uWord I;
	uWord PC;
	uWord SP;
};

