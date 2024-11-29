#include "ProgramManager.h"

int main(int argc, char** argv)
{
	chip8cpu cpu;
	Memory memory;
	DisplayManager display;

	ProgramManager program(cpu, memory, display);

	program.runProgram();
	display.DisplayQuit();

	return 0;
}