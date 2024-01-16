#include "Memory.h"

/* Public methods */

Memory::Memory()
{
	Memory::clearMem();
	Memory::loadFonts();
}

uByte Memory::operator[](uWord index) const
{
	return data[index];
}

void Memory::setByte(uWord index, uByte value)
{
	if (index < RAM_START)
	{
		throw "Trying to write in ROM Memory";
	}
	else if (index > MEM_SIZE)
	{
		throw "Trying to write out of Memory";
	}
	else
	{
		data[index] = value;
	}
}

/* Private methods */

void Memory::clearMem()
{
	for (int i = RAM_START; i < MEM_SIZE; i++)
	{
		data[i] = 0;
	}
}

void Memory::loadFonts()
{
	/* 0 */
	data[0x00] = 0b11110000;
	data[0x01] = 0b10010000;
	data[0x02] = 0b10010000;
	data[0x03] = 0b10010000;
	data[0x04] = 0b11110000;

	/* 1 */
	data[0x05] = 0b00100000;
	data[0x06] = 0b01100000;
	data[0x07] = 0b00100000;
	data[0x08] = 0b00100000;
	data[0x09] = 0b01110000;

	/* 2 */
	data[0x0A] = 0b11110000;
	data[0x0B] = 0b00010000;
	data[0x0C] = 0b11110000;
	data[0x0D] = 0b10000000;
	data[0x0E] = 0b11110000;

	/* 3 */
	data[0x0F] = 0b11110000;
	data[0x10] = 0b00010000;
	data[0x11] = 0b11110000;
	data[0x12] = 0b00010000;
	data[0x13] = 0b11110000;

	/* 4 */
	data[0x14] = 0b10010000;
	data[0x15] = 0b10010000;
	data[0x16] = 0b11110000;
	data[0x17] = 0b00010000;
	data[0x18] = 0b00010000;

	/* 5 */
	data[0x19] = 0b11110000;
	data[0x1A] = 0b10000000;
	data[0x1B] = 0b11110000;
	data[0x1C] = 0b00010000;
	data[0x1D] = 0b11110000;

	/* 6 */
	data[0x1E] = 0b11110000;
	data[0x1F] = 0b10000000;
	data[0x20] = 0b11110000;
	data[0x21] = 0b10010000;
	data[0x22] = 0b11110000;

	/* 7 */
	data[0x23] = 0b11110000;
	data[0x24] = 0b00010000;
	data[0x25] = 0b00100000;
	data[0x26] = 0b01000000;
	data[0x27] = 0b01000000;

	/* 8 */
	data[0x28] = 0b11110000;
	data[0x29] = 0b10010000;
	data[0x2A] = 0b11110000;
	data[0x2B] = 0b10010000;
	data[0x2C] = 0b11110000;

	/* 9 */
	data[0x2D] = 0b11110000;
	data[0x2E] = 0b10010000;
	data[0x2F] = 0b11110000;
	data[0x30] = 0b00010000;
	data[0x31] = 0b11110000;

	/* A */
	data[0x32] = 0b11110000;
	data[0x33] = 0b10010000;
	data[0x34] = 0b11110000;
	data[0x35] = 0b10010000;
	data[0x36] = 0b10010000;

	/* B */
	data[0x37] = 0b11100000;
	data[0x38] = 0b10010000;
	data[0x39] = 0b11100000;
	data[0x3A] = 0b10010000;
	data[0x3B] = 0b11100000;

	/* C */
	data[0x3C] = 0b11110000;
	data[0x3D] = 0b10000000;
	data[0x3E] = 0b10000000;
	data[0x3F] = 0b10000000;
	data[0x40] = 0b11110000;

	/* D */
	data[0x41] = 0b11100000;
	data[0x42] = 0b10010000;
	data[0x43] = 0b10010000;
	data[0x44] = 0b10010000;
	data[0x45] = 0b11100000;

	/* E */
	data[0x46] = 0b11110000;
	data[0x47] = 0b10000000;
	data[0x48] = 0b11110000;
	data[0x49] = 0b10000000;
	data[0x4A] = 0b11110000;

	/* F */
	data[0x4B] = 0b11110000;
	data[0x4C] = 0b10000000;
	data[0x4D] = 0b11110000;
	data[0x4E] = 0b10000000;
	data[0x4F] = 0b10000000;
}