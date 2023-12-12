#include "Display_Keyboard.h"
#include "ProgramManager.h"

//TODO: Arreglar bugs; Ordenar código
int main(int argc, char** argv)
{
	DisplayAndKeyboard_Manager::initDisplay();

	chip8cpu cpu;
	Memory memory;
	ProgramManager program(cpu, memory);
	program.runProgram();

	DisplayAndKeyboard_Manager::endDisplay();

	return 0;
}