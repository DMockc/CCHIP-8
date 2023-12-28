#include "ProgramManager.h"

//TODO: Arreglar bugs; Ordenar código; Arreglar colisiones (VF Register)
int main(int argc, char** argv)
{
	chip8cpu cpu;
	Memory memory;
	DisplayManager display;

	ProgramManager program(cpu, memory, display);

	program.runProgram();

	return 0;
}