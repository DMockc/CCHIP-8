#pragma once

using uByte = unsigned char;
using uWord = unsigned short;

/* Buffer operations
* Used to make a copy of the numbers of an instruction in the buffer to operate with them
*/
void loadNumberToBuffer(uWord& buffer, uByte N1);
void loadNumberToBuffer(uWord& buffer, uByte N1, uByte N2);
void loadNumberToBuffer(uWord& buffer, uByte N1, uByte N2, uByte N3);
void clearBuffer(uWord& buffer);