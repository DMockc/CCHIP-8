#include "ProgramManager.h"

/*
* TODO:
* Arreglar bugs(Sobretodo el Connect 4, al manterner un bot�n que no sirve mientras se usa otro que s� el sprite se duplica m�gicamente)
* Ordenar c�digo
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