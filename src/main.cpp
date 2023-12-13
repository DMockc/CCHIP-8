#include "ProgramManager.h"

//TODO: Arreglar bugs; Ordenar código
// IMPORTANTE -> Encargarse de screenMatrix
int main(int argc, char** argv)
{
	chip8cpu cpu;
	Memory memory;
	DisplayManager display;
	KeyboardManager keyboard;

	ProgramManager program(cpu, memory, display, keyboard);

	program.runProgram();

	return 0;
}