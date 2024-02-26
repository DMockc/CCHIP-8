#include "ProgramManager.h"

/*
* TODO:
* Ordenar código (Display)
*/

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