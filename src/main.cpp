#include "ProgramManager.h"

/*
* TODO:
* Arreglar bugs: Pong (no hay colisiones)
* Ordenar código
*/

int main(int argc, char** argv)
{
	chip8cpu cpu;
	Memory memory;
	DisplayManager display;

	ProgramManager program(cpu, memory, display);

	program.runProgram();

	return 0;
}