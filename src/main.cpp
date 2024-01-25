#include "ProgramManager.h"

/*
* TODO:
* Arreglar velocidad al escribir el speed en pantalla
* Ordenar código (Display)
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