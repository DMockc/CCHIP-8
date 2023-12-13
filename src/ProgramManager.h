#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>


#include "chip8cpu.h"
#include "Memory.h"
#include "DisplayManager.h"
#include "KeyboardManager.h"
#include "fileManager.h"


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
	ProgramManager(chip8cpu& cpu, Memory& mem, DisplayManager& display, KeyboardManager& keyboard);

	void loadProgram(const char* filepath);
	void runProgram();

private:

	inline void loadNumberToBuffer(uWord& buffer, uByte N1);
	inline void loadNumberToBuffer(uWord& buffer, uByte N1, uByte N2);
	inline void loadNumberToBuffer(uWord& buffer, uByte N1, uByte N2, uByte N3);
	inline void clearBuffer(uWord& buffer);

	inline void execute(Instruction& instruction);
	inline void loadInstruction(Instruction& instruction, uWord& PC);
	int m_program_size = 0;


	Memory m_memory;
	chip8cpu m_cpu;
	DisplayManager m_display;
	KeyboardManager m_keyboard;
};