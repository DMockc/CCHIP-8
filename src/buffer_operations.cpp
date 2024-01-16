#include "buffer_operations.h"

void loadNumberToBuffer(uWord& buffer, uByte N1)
{
	buffer |= N1;
}

void loadNumberToBuffer(uWord& buffer, uByte N1, uByte N2)
{
	buffer = (N1 << 4) | N2;
}

void loadNumberToBuffer(uWord& buffer, uByte N1, uByte N2, uByte N3)
{
	buffer = (N1 << 8) | ((N2 << 4) | N3);
}

void clearBuffer(uWord& buffer)
{
	buffer = 0;
}