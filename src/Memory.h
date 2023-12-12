#pragma once

#define MEM_SIZE 0xFFF
#define RAM_START 0x200

using uByte = unsigned char;
using uWord = unsigned short;

class Memory
{
public:

	Memory();

	/* Getter */
	uByte operator[](uWord index) const;

	/* Setter */
	void setByte(uWord index, uByte value);
	
	void clearMem();

	uWord stack[0xFF];

private:

	void loadFonts();

	uByte data[MEM_SIZE];
};

