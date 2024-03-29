#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>

#include "chip8cpu.h"
#include "Memory.h"
#include "DisplayManager.h"
#include "KeyboardManager.h"
#include "fileManager.h"
#include "instruction_set.h"
#include "buffer_operations.h"

typedef struct
{

	uByte FirstQuarter : 4;
	uByte SecondQuarter : 4;
	uByte ThirdQuarter : 4;
	uByte FourthQuarter : 4;

} Instruction;

class ProgramManager
{
public:
	ProgramManager(chip8cpu& cpu, Memory& mem, DisplayManager& display);

	void loadProgram(const char* filepath);
	void runProgram();

private:
	void execute(Instruction& instruction);
	void loadInstruction(Instruction& instruction, uWord& PC);
	int m_program_size = 0;


	Memory m_memory;
	chip8cpu m_cpu;
	DisplayManager m_display;
	SDL_Event m_windowEvent;
};