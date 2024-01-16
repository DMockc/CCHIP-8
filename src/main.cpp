#include "ProgramManager.h"

/*
* TODO:
* Arreglar bugs(Sobretodo el Connect 4, al manterner un botón que no sirve mientras se usa otro que sí el sprite se duplica mágicamente)
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