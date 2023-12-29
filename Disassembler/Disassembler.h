#pragma once
#include <iostream>
#include <fstream>

namespace Disassembler
{
	union Instruction
	{
		unsigned short FullInstruction;

		struct
		{
			unsigned short FourthQuarter : 4;
			unsigned short ThirdQuarter : 4;
			unsigned short SecondQuarter : 4;
			unsigned short FirstQuarter : 4;
		};
	};

	void disassembly(char* buffer, size_t size);

	void extractInstructions(Instruction& instruction);
}; //namespace: Disassembler

