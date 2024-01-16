#pragma once
//(00E0): Clear the display by setting all pixels to black
#define CLS				0x0

//(00EE): Return from a subroutine. Pops the value at the top of the stack (indicated by the stack pointer SP) and puts it in PC
#define RET				0xE

//(1NNN): Jump to address in NNN. Sets the PC to NNN
#define JMP_NNN			0x1

//(2NNN): Call the subroutine at address NNN. It increments SP, puts the current PC at the top of the stack and sets PC to the address NNN
#define CALL_NNN		0x2

//(3XNN): Skip the next instruction if VX == NN
#define SE_VX_NN		0x3

//(4XNN): Skip the next instruction if VX != NN
#define SNE_VX_NN		0x4

//(5XY0): Skip the next instruction if VX == VY
#define SE_VX_VY		0x5

//(6XNN): Load the value NN into the register VX
#define LD_VX_NN		0x6

//(7XNN): Add the value NN to the value of register VX and store the result in VX
#define ADD_VX_NN		0x7

//Bitwise operations
#define BITWISE_OP		0x8

//(8XY0): Put the value of register VY into VX
#define LD_VX_VY		0x0

//(8XV1): Perform a bitwise OR between the values of VX and VY and store the result in VX
#define OR_VX_VY		0x1

//(8XY2): Perform a bitwise AND between the values of VX and VY and store the result in VX
#define AND_VX_VY		0x2

//(8XY3): Perform a bitwise XOR between the values of VX and VY and store the result in VX
#define XOR_VX_VY		0x3

//(8XY4): Add the values of VX and VY and store the result in VX. Put the carry bit in VF (if there is overflow, set VF to 1, otherwise 0)
#define ADD_VX_VY		0x4

//(8XY5): Subtract the value of VY from VX and store the result in VX. Put the borrow in VF (if there is borrow, set VF to 1, otherwise 0)
#define SUB_VX_VY		0x5

//(8XY6): Shift right, or divide VX by two. Store the least significant bit of VX in VF, and then divide VX and store its value in VX
#define SHR_VX			0x6

//(8XY7): Subtract the value of VY from VX and store the result in VX. Set VF to 1 if there is no borrow, to 0 otherwise
#define SUBN_VX_VY		0x7

//(8XYE): Shift left, or multiply VX by two. Store the most significant bit of VX in VF, and then multiply VX and store its value in VX
#define SHL_VX			0xE

//(9XY0): Skip the next instruction if the values of VX and VY are not equal
#define SNE_VX_VY		0x9

//(ANNN): Set the value of I to the address NNN
#define LD_I_NNN		0xA

//(BNNN): Jump to the location NNN + V0
#define JMP_V0_NNN		0xB

//(CXNN): Generate a random byte (from 0 to 255), do a bitwise AND with NN and store the result to VX
#define RND_VX_NN		0xC

/*
* (DXYN):
	*The draw instruction.This is arguably the most involved operation
	* The n - byte sprite starting at the address I is drawn to the display at the coordinates[VX, VY]
	* Then, set VF to 1 if there has been a collision(a display bit was changed from 1 to 0)
	* The interpreter must read N bytes from the I address in memory
	* These bytes are interpreted as a sprite and drawn at the display coordinates[VX, VY]
	* The bits are set using an XOR with the current display state
*/
#define DRW_VX_VY_N		0xD

//Keyboard operations
#define KEYBOARD_OP		0xE

//(EX9E): Skip the next instruction if the key with the value of VX is currently pressed.
#define SKP_VX			0xE


//(EXA1): Skip the next instruction if the key with the value of VX is currently not pressed.
#define SKNP_VX			0x1

//Main registers operations
#define REGISTER_OP		0xF

//(FX07): Read the delay timer register value into VX
#define LD_VX_DT		0x07

//(FX0A): Wait for a key press, and then store the value of the key to VX
#define LD_VX_K			0x0A

//(FX15): Load the value of VX into the delay timer DT
#define LD_DT_VX		0x15

//(FX18): Load the value of VX into the sound time ST
#define LD_ST_VX		0x18

//(FX1E): Add the values of I and VX, and store the result in I
#define ADD_I_VX		0x1E

/*
* (FX29): 
	* Set the location of the sprite for the digit VX to I.
	* The font sprites start at address 0x000, and contain the hexadecimal digits from 1..F. Each font has a length of 0x05 bytes.
	* The memory address for the value in VX is put in I.
*/
#define LD_F_VX			0x29

/*
* (FX33):
	* Store the binary-coded decimal in VX and put it in three consecutive memory slots starting at I.
	* VX is a byte, so it is in 0…255. The interpreter takes the value in VX (for example the decimal value 174, or 0xAE in hex),
	* converts it into a decimal and separates the hundreds, the tens and the ones (1, 7 and 4 respectively).
	* Then, it stores them in three memory locations starting at I (1 to I, 7 to I+1 and 4 to I+2)
*/
#define LD_B_VX			0x33

//(FX55): Store registers from V0 to VX in the main memory, starting at location I.
#define LD_I_VX			0x55

//(FX65): Load the memory data starting at address I into the registers V0 to VX
#define LD_VX_I			0x65


#define UNKNOWN_INSTRUCTION std::cerr << "Unknown instruction: 0x" \
	<< std::hex << std::uppercase << static_cast<int>(instruction.FirstQuarter) \
	<< static_cast<int>(instruction.SecondQuarter) \
	<< static_cast<int>(instruction.ThirdQuarter) \
	<< static_cast<int>(instruction.FourthQuarter) << "\n"