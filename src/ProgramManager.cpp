#include "ProgramManager.h"

#ifndef _DEBUG
#define DEBUG(x)
#endif // DEBUG
#define DEBUG(x) std::cout << x << "\n"

ProgramManager::ProgramManager(chip8cpu& cpu, Memory& mem)
	: m_cpu(cpu), m_memory(mem) {}

#pragma region Public Methods
void ProgramManager::loadProgram(const char* file_path)
{
	if (!checkExtension(file_path))
	{
		std::cerr << " File extension isn't correct!\n";
		return;
	}

	std::ifstream file(file_path, std::ios::binary | std::ios::ate);
	std::pair<char*, int> buffer = loadFileInBuffer(file);

	if (buffer.first == nullptr && buffer.second == NULL)
	{
		std::cerr << "File couldn't be opened!\n";
		return;
	}

	for (int i = 0; (RAM_START + i) < MEM_SIZE && i < static_cast<int>(buffer.second); i++)
	{
		m_memory.setByte(RAM_START + i, buffer.first[i]);
	}

	delete[] buffer.first;

	m_program_size = static_cast<int>(buffer.second);

	std::cout << "Program loaded!\n";

	SDL_Delay(1000);
}

void ProgramManager::runProgram()
{
	Instruction actualInstruction;
	bool isRunning = true;
	SDL_Event windowEvent;

	bool speedUp = false;
	bool slowDown = false;

	unsigned int FPS_LIMIT = 1000;

	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	while (isRunning)
	{
		//DEBUG(std::dec << m_cpu.PC << " | " << std::hex << static_cast<int>(m_memory[m_cpu.PC]));

		//DEBUG(std::hex << static_cast<int>(m_memory[m_cpu.PC]) << std::dec << " - " << m_cpu.PC);

		unsigned int desiredDelta = 1000 / FPS_LIMIT;
		Uint32 startLoop = SDL_GetTicks();

		if (SDL_PollEvent(&windowEvent))
		{
			switch (windowEvent.type)
			{
#pragma region KEYDOWN
			case SDL_KEYDOWN:

				switch (windowEvent.key.keysym.sym)
				{

				case SDLK_o: //Speed up
					if (!slowDown) {
						if (!speedUp) {
							FPS_LIMIT <<= 1;
							speedUp = true;
						}
						else
						{
							FPS_LIMIT >>= 1;
							speedUp = false;
						}
					}

					break;

				case SDLK_i: //Slow down
					if (!speedUp) {
						if (!slowDown) {
							FPS_LIMIT >>= 1;
							slowDown = true;
						}
						else
						{
							FPS_LIMIT <<= 1;
							slowDown = false;
						}
					}

					break;



				case SDLK_1:
					DisplayAndKeyboard_Manager::keymap[0x01] = true;
					break;

				case SDLK_2:
					DisplayAndKeyboard_Manager::keymap[0x02] = true;
					break;

				case SDLK_3:
					DisplayAndKeyboard_Manager::keymap[0x03] = true;
					break;

				case SDLK_4:
					DisplayAndKeyboard_Manager::keymap[0x0C] = true;
					break;

				case SDLK_q:
					DisplayAndKeyboard_Manager::keymap[0x04] = true;
					break;

				case SDLK_w:
					DisplayAndKeyboard_Manager::keymap[0x05] = true;
					break;

				case SDLK_e:
					DisplayAndKeyboard_Manager::keymap[0x06] = true;
					break;

				case SDLK_r:
					DisplayAndKeyboard_Manager::keymap[0x0D] = true;
					break;

				case SDLK_a:
					DisplayAndKeyboard_Manager::keymap[0x07] = true;
					break;

				case SDLK_s:
					DisplayAndKeyboard_Manager::keymap[0x08] = true;
					break;

				case SDLK_d:
					DisplayAndKeyboard_Manager::keymap[0x09] = true;
					break;

				case SDLK_f:
					DisplayAndKeyboard_Manager::keymap[0x0E] = true;
					break;

				case SDLK_z:
					DisplayAndKeyboard_Manager::keymap[0x0A] = true;
					break;

				case SDLK_x:
					DisplayAndKeyboard_Manager::keymap[0x00] = true;
					break;

				case SDLK_c:
					DisplayAndKeyboard_Manager::keymap[0x0B] = true;
					break;

				case SDLK_v:
					DisplayAndKeyboard_Manager::keymap[0x0F] = true;
					break;

				default:
					break;
				}

				break;
#pragma endregion
#pragma region KEYUP
			case SDL_KEYUP:

				switch (windowEvent.key.keysym.sym)
				{
				case SDLK_1:
					DisplayAndKeyboard_Manager::keymap[0x01] = false;
					break;

				case SDLK_2:
					DisplayAndKeyboard_Manager::keymap[0x02] = false;
					break;

				case SDLK_3:
					DisplayAndKeyboard_Manager::keymap[0x03] = false;
					break;

				case SDLK_4:
					DisplayAndKeyboard_Manager::keymap[0x0C] = false;
					break;

				case SDLK_q:
					DisplayAndKeyboard_Manager::keymap[0x04] = false;
					break;

				case SDLK_w:
					DisplayAndKeyboard_Manager::keymap[0x05] = false;
					break;

				case SDLK_e:
					DisplayAndKeyboard_Manager::keymap[0x06] = false;
					break;

				case SDLK_r:
					DisplayAndKeyboard_Manager::keymap[0x0D] = false;
					break;

				case SDLK_a:
					DisplayAndKeyboard_Manager::keymap[0x07] = false;
					break;

				case SDLK_s:
					DisplayAndKeyboard_Manager::keymap[0x08] = false;
					break;

				case SDLK_d:
					DisplayAndKeyboard_Manager::keymap[0x09] = false;
					break;

				case SDLK_f:
					DisplayAndKeyboard_Manager::keymap[0x0E] = false;
					break;

				case SDLK_z:
					DisplayAndKeyboard_Manager::keymap[0x0A] = false;
					break;

				case SDLK_x:
					DisplayAndKeyboard_Manager::keymap[0x00] = false;
					break;

				case SDLK_c:
					DisplayAndKeyboard_Manager::keymap[0x0B] = false;
					break;

				case SDLK_v:
					DisplayAndKeyboard_Manager::keymap[0x0F] = false;
					break;

				default:
					break;
				}

				break;
#pragma endregion

			case SDL_DROPFILE:
				SDL_SetRenderDrawColor(DisplayAndKeyboard_Manager::renderer, BLACK);
				SDL_RenderClear(DisplayAndKeyboard_Manager::renderer);
				
				m_cpu.resetCPU();

				m_memory.clearMem();

				for (int i = 0; i < DisplayAndKeyboard_Manager::HEIGHT; i++)
				{
					for (int j = 0; j < DisplayAndKeyboard_Manager::WIDTH; j++)
					{
						DisplayAndKeyboard_Manager::screenMatrix[i][j] = 0;
					}
				}

				DisplayAndKeyboard_Manager::coords_buffer.clear();

				loadProgram(windowEvent.drop.file);
				SDL_free(windowEvent.drop.file);
				break;

			case SDL_QUIT:
				isRunning = false;
				break;

			default:
				break;
			}
		}

		if (m_program_size == 0) continue;

		if (m_cpu.PC < MEM_SIZE)
		{
			loadInstruction(actualInstruction, m_cpu.PC);
			execute(actualInstruction);
		}
		else
		{
			std::cout << "Program finished!\n";
			m_program_size = 0;
			continue;
		}

		m_cpu.updateDT();
		m_cpu.updateST();

		DisplayAndKeyboard_Manager::drawMatrix(8);


		SDL_RenderPresent(DisplayAndKeyboard_Manager::renderer);

		/* FPS Limitation */
		Uint32 delta = SDL_GetTicks() - startLoop;
		if (delta < desiredDelta)
		{
			SDL_Delay(desiredDelta - delta);
		}

		//SDL_Log("%d | %d\n", m_cpu.DT, m_cpu.ST);
		
	}
}
#pragma endregion

/* Buffer operations
* Used to make a copy of the numbers of an instruction in the buffer to operate with them
*/
#pragma region Buffer Operatios
inline void ProgramManager::loadNumberToBuffer(uWord& buffer, uByte N1)
{
	buffer |= N1;
}

inline void ProgramManager::loadNumberToBuffer(uWord& buffer, uByte N1, uByte N2)
{
	buffer = (N1 << 4) | N2;
}

inline void ProgramManager::loadNumberToBuffer(uWord& buffer, uByte N1, uByte N2, uByte N3)
{
	buffer = (N1 << 8) | ((N2 << 4) | N3);
}

inline void ProgramManager::clearBuffer(uWord& buffer)
{
	buffer = 0;
}

#pragma endregion


void ProgramManager::loadInstruction(Instruction& instruction, uWord& PC)
{
	uByte buffer = m_memory[PC];
	instruction.FirstQuarter = 0;
	instruction.SecondQuarter = 0;
	instruction.ThirdQuarter = 0;
	instruction.FourthQuarter = 0;


	instruction.FirstQuarter |= (buffer >> 4);
	instruction.SecondQuarter = 0x0F;
	instruction.SecondQuarter &= buffer;

	PC++;
	buffer = m_memory[PC];
	
	instruction.ThirdQuarter |= (buffer >> 4);
	instruction.FourthQuarter = 0x0F;
	instruction.FourthQuarter &= buffer;

	PC++;
}

void ProgramManager::execute(Instruction& instruction)
{
	uWord operator_buffer = 0;

	uByte pressedKey = 0;

	uByte xcoord = 0;
	uByte ycoord = 0;

	switch (instruction.FirstQuarter)
	{
	case 0x0:

		switch (instruction.FourthQuarter)
		{

		case 0x0: //CLS (00E0): Clear the display by setting all pixels to ‘off’.
			SDL_SetRenderDrawColor(DisplayAndKeyboard_Manager::renderer, BLACK);
			SDL_RenderClear(DisplayAndKeyboard_Manager::renderer);
			
			for (int i = 0; i < DisplayAndKeyboard_Manager::HEIGHT; i++)
			{
				for (int j = 0; j < DisplayAndKeyboard_Manager::WIDTH; j++)
				{
					DisplayAndKeyboard_Manager::screenMatrix[i][j] = 0;
				}
			}

			break;


		case 0xE: //RET (00EE): Return from a subroutine. Pops the value at the top of the stack (indicated by the stack pointer SP) and puts it in PC
			m_cpu.PC = m_memory.stack[m_cpu.SP];
			m_cpu.SP--;

			break;


		default: //Unknown instruction
			std::cerr << "Unknown instruction: 0x" << std::hex << static_cast<int>(instruction.FirstQuarter) << static_cast<int>(instruction.SecondQuarter) << static_cast<int>(instruction.ThirdQuarter) << static_cast<int>(instruction.FourthQuarter) << "\n";
			exit(-1);
			break;
		}

		break;


	case 0x1: //JMP (1NNN): Jump to address in NNN. Sets the PC to NNN
		loadNumberToBuffer(operator_buffer, instruction.SecondQuarter, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.PC = operator_buffer;

		clearBuffer(operator_buffer);
		break;


	case 0x2: //CALL NNN (2NNN): Call the subroutine at address NNN. It increments SP, puts the current PC at the top of the stack and sets PC to the address NNN
		m_cpu.SP++;

		m_memory.stack[m_cpu.SP] = m_cpu.PC;

		loadNumberToBuffer(operator_buffer, instruction.SecondQuarter, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.PC = operator_buffer;

		clearBuffer(operator_buffer);
		break;


	case 0x3: //SE VX, NN (3XNN): Skip the next instruction if VX == NN. Compare the value of register VX with NN and if they are equal, increment PC by two.
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);

		if (m_cpu.V[instruction.SecondQuarter] == operator_buffer)
		{
			m_cpu.PC += 2;
		}

		clearBuffer(operator_buffer);
		break;


	case 0x4: //SNE VX, NN (4XNN): Skip the next instruction if VX != NN. Compare the value of register VX with NN and if they are not equal, increment PC by two.
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);

		if (m_cpu.V[instruction.SecondQuarter] != operator_buffer)
		{
			m_cpu.PC += 2;
		}

		clearBuffer(operator_buffer);
		break;


	case 0x5: //SE VX, VY (5XY0): Skip the next instruction if VX == VY. Compare the value of register VX with the value of VY and if they are equal, increment PC by two.

		if (m_cpu.V[instruction.SecondQuarter] == m_cpu.V[instruction.ThirdQuarter])
		{
			m_cpu.PC += 2;
		}

		break;


	case 0x6: //LD VX, NN (6XNN): Load the value NN into the register VX
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.V[instruction.SecondQuarter] = static_cast<uByte>(operator_buffer);

		clearBuffer(operator_buffer);
		break;


	case 0x7: //ADD VX, NN (7XNN): Add the value NN to the value of register VX and store the result in VX
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.V[instruction.SecondQuarter] += operator_buffer;

		clearBuffer(operator_buffer);
		break;

	case 0x8: //Bitwise operations
		switch (instruction.FourthQuarter)
		{
		case 0x0: //LD VX, VY (8XY0): Put the value of register VY into VX
			m_cpu.V[instruction.SecondQuarter] = m_cpu.V[instruction.ThirdQuarter];

			break;


		case 0x1: //OR VX, VY (8XV1): Perform a bitwise OR between the values of VX and VY and store the result in VX
			m_cpu.V[instruction.SecondQuarter] |= m_cpu.V[instruction.ThirdQuarter];

			break;


		case 0x2: //AND VX, VY (8XY2): Perform a bitwise AND between the values of VX and VY and store the result in VX
			m_cpu.V[instruction.SecondQuarter] &= m_cpu.V[instruction.ThirdQuarter];

			break;


		case 0x3: //XOR VX, VY (8XY3): Perform a bitwise XOR between the values of VX and VY and store the result in VX
			m_cpu.V[instruction.SecondQuarter] ^= m_cpu.V[instruction.ThirdQuarter];

			break;


		case 0x4: //ADD VX, VY (8XY4): Add the values of VX and VY and store the result in VX. Put the carry bit in VF (if there is overflow, set VF to 1, otherwise 0)
			if (m_cpu.V[instruction.SecondQuarter] + m_cpu.V[instruction.ThirdQuarter] > 0xFF)
			{
				m_cpu.V[0xF] = 1;
			}
			else
			{
				m_cpu.V[0xF] = 0;
			}

			m_cpu.V[instruction.SecondQuarter] += m_cpu.V[instruction.ThirdQuarter];

			break;


		case 0x5: //SUB VX, VY (8XY5): Subtract the value of VY from VX and store the result in VX. Put the borrow in VF (if there is borrow, VX > VY, set VF to 1, otherwise 0)
			if (m_cpu.V[instruction.SecondQuarter] > m_cpu.V[instruction.ThirdQuarter])
			{
				m_cpu.V[0xF] = 1;
			}
			else
			{
				m_cpu.V[0xF] = 0;
			}

			m_cpu.V[instruction.SecondQuarter] -= m_cpu.V[instruction.ThirdQuarter];

			break;


		case 0x6: //SHR VX {, VY} (8XY6): Shift right, or divide VX by two. Store the least significant bit of VX in VF, and then divide VX and store its value in VX

			m_cpu.V[0xF] = m_cpu.V[instruction.SecondQuarter] & 0x01;

			m_cpu.V[instruction.SecondQuarter] >>= 1;

			break;


		case 0x7: //SUBN VX, VY (8XY7): Subtract the value of VY from VX and store the result in VX. Set VF to 1 if there is no borrow, to 0 otherwise
			if (m_cpu.V[instruction.ThirdQuarter] > m_cpu.V[instruction.SecondQuarter])
			{
				m_cpu.V[0xF] = 1;
			}
			else
			{
				m_cpu.V[0xF] = 0;
			}

			m_cpu.V[instruction.ThirdQuarter] -= m_cpu.V[instruction.SecondQuarter];

			break;


		case 0xE: //SHL VX {, VY} (8XYE): Shift left, or multiply VX by two. Store the most significant bit of VX in VF, and then multiply VX and store its value in VX
			m_cpu.V[0xF] = m_cpu.V[instruction.SecondQuarter] & 0x80;

			m_cpu.V[instruction.SecondQuarter] <<= 1;

			break;


		default:
			std::cerr << "Unknown instruction: 0x" << std::hex << static_cast<int>(instruction.FirstQuarter) << static_cast<int>(instruction.SecondQuarter) << static_cast<int>(instruction.ThirdQuarter) << static_cast<int>(instruction.FourthQuarter) << "\n";
			exit(-1);
			break;
		}

		clearBuffer(operator_buffer);
		break;

	case 0x9: //SNE VX, VY (9XY0): Skip the next instruction if the values of VX and VY are not equal

		if (m_cpu.V[instruction.SecondQuarter] != m_cpu.V[instruction.ThirdQuarter])
		{
			m_cpu.PC += 2;
		}

		break;


	case 0xA: //LD I, NNN (ANNN): Set the value of I to the address NNN
		loadNumberToBuffer(operator_buffer, instruction.SecondQuarter, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.I = operator_buffer;

		clearBuffer(operator_buffer);
		break;


	case 0xB: //JMP V0, NNN (BNNN): Jump to the location NNN + V0
		loadNumberToBuffer(operator_buffer, instruction.SecondQuarter, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.PC = m_cpu.V[0x0] + operator_buffer;

		clearBuffer(operator_buffer);
		break;


	case 0xC: //RND VX, NN (CXNN): Generate a random byte (from 0 to 255), do a bitwise AND with NN and store the result to VX
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.V[instruction.SecondQuarter] = (rand() % 256) & operator_buffer;

		srand(static_cast<unsigned int>(time(NULL)));

		clearBuffer(operator_buffer);
		break;


	case 0xD: /*DRW VX, VY, N (DXYN):
		* The draw instruction. This is arguably the most involved operation
		* The n-byte sprite starting at the address I is drawn to the display at the coordinates [VX, VY]
		* Then, set VF to 1 if there has been a collision (a display bit was changed from 1 to 0)
		* The interpreter must read N bytes from the I address in memory
		* These bytes are interpreted as a sprite and drawn at the display coordinates [VX, VY]
		* The bits are set using an XOR with the current display state
		*/

		xcoord = m_cpu.V[instruction.SecondQuarter] % DisplayAndKeyboard_Manager::WIDTH;
		ycoord = m_cpu.V[instruction.ThirdQuarter] % DisplayAndKeyboard_Manager::HEIGHT;

		try //Checks if I points to ROM Memory
		{
			for (int row = 0; row < instruction.FourthQuarter; row++)
			{

				uByte y_selectedCoord = (ycoord + row) % DisplayAndKeyboard_Manager::HEIGHT;

				for (int column = 0; column < 8; column++)
				{
					bool collision = false;

					uByte x_selectedCoord = (xcoord + column) % DisplayAndKeyboard_Manager::WIDTH;

					operator_buffer = (m_memory[m_cpu.I + row] << column) & 0x80; //Select a bit of the byte

					if (DisplayAndKeyboard_Manager::screenMatrix[y_selectedCoord][x_selectedCoord] == 1 && ((operator_buffer >> 7) & 0x01) && collision == false)
					{
						m_cpu.V[0xF] = 1;
						collision = true;
					}
					else
					{
						m_cpu.V[0xF] = 0;
						collision = true;
					}

					DisplayAndKeyboard_Manager::screenMatrix[y_selectedCoord][x_selectedCoord] ^= (operator_buffer >> 7) & 0x01; //Makes XOR in [x, y]
					
					DisplayAndKeyboard_Manager::coords_buffer.push_back(
						DRW_COORD(
							y_selectedCoord,
							x_selectedCoord, 
							DisplayAndKeyboard_Manager::screenMatrix[y_selectedCoord][x_selectedCoord]
						)
					); 

					clearBuffer(operator_buffer);

					if (x_selectedCoord >= DisplayAndKeyboard_Manager::WIDTH - 1) //Reachs X limit
					{
						break;
					}

				}
				if (y_selectedCoord >= DisplayAndKeyboard_Manager::HEIGHT - 1) //Reachs Y limit
				{
					break;
				}
			}
		}
		catch (const char* error)
		{
			std::cerr << error;
			exit(-1);
		}

		clearBuffer(operator_buffer);
		break;


	case 0xE: 
		switch (instruction.FourthQuarter)
		{
		case 0xE: /*SKP VX (EX9E) : Skip the next instruction if the key with the value of VX is currently pressed.
		* Basically, increase PC by two if the key corresponding to the value in VX is pressed. */

			if (DisplayAndKeyboard_Manager::isPressed(m_cpu.V[instruction.SecondQuarter]))
			{
				m_cpu.PC += 2;
			}

			break;

		case 0x1: /* SKNP VX(EXA1) : Skip the next instruction if the key with the value of VX is currently not pressed.
			* Basically, increase PC by two if the key corresponding to the value in VX is not pressed. */

			if (!DisplayAndKeyboard_Manager::isPressed(m_cpu.V[instruction.SecondQuarter]))
			{
				m_cpu.PC += 2;
			}

			break;


		default:
			std::cerr << "Unknown instruction: 0x" << std::hex << static_cast<int>(instruction.FirstQuarter) << static_cast<int>(instruction.SecondQuarter) << static_cast<int>(instruction.ThirdQuarter) << static_cast<int>(instruction.FourthQuarter) << "\n";
			exit(-1);
			break;
		}

		clearBuffer(operator_buffer);
		break;


	case 0xF: //https://tonisagrista.com/blog/2021/chip8-spec/#sknp-vx-----exa1
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);

		switch (operator_buffer)
		{
		case 0x07: //LD VX, DT (FX07): Read the delay timer register value into VX
			m_cpu.V[instruction.SecondQuarter] = m_cpu.DT;

			break;


		case 0x0A: //LD VX, K (FX0A): Wait for a key press, and then store the value of the key to VX
			
			if (_kbhit())
			{
				pressedKey = _getch();
				m_cpu.V[instruction.SecondQuarter] = pressedKey;
				pressedKey = 0;
			}
			else
			{
				m_cpu.PC -= 2; //Re-load the instruction
			}

			break;


		case 0x15: //LD DT, VX (FX15): Load the value of VX into the delay timer DT
			m_cpu.DT = m_cpu.V[instruction.SecondQuarter];

			break;


		case 0x18: //LD ST, VX (FX18): Load the value of VX into the sound time ST
			m_cpu.ST = m_cpu.V[instruction.SecondQuarter];

			break;


		case 0x1E: //ADD I, VX (FX1E): Add the values of I and VX, and store the result in I
			m_cpu.I += m_cpu.V[instruction.SecondQuarter];

			break;


		case 0x29: /* LD F, VX (FX29): Set the location of the sprite for the digit VX to I.
			The font sprites start at address 0x000, and contain the hexadecimal digits from 1..F. Each font has a length of 0x05 bytes. 
			The memory address for the value in VX is put in I. */
			m_cpu.I = m_cpu.V[instruction.SecondQuarter] * 0x05;

			break;


		case 0x33: /* LD B, VX (FX33): Store the binary-coded decimal in VX and put it in three consecutive memory slots starting at I.
			* VX is a byte, so it is in 0…255. The interpreter takes the value in VX (for example the decimal value 174, or 0xAE in hex),
			* converts it into a decimal and separates the hundreds, the tens and the ones (1, 7 and 4 respectively). 
			* Then, it stores them in three memory locations starting at I (1 to I, 7 to I+1 and 4 to I+2)*/
			m_memory.setByte(m_cpu.I, m_cpu.V[instruction.SecondQuarter] / 100);
			m_memory.setByte(m_cpu.I + 1, (m_cpu.V[instruction.SecondQuarter] - m_memory[m_cpu.I] * 100) / 10);
			m_memory.setByte(m_cpu.I + 2, m_cpu.V[instruction.SecondQuarter] - m_memory[m_cpu.I] * 100 - m_memory[m_cpu.I + 1] * 10);

			break;


		case 0x55: /* LD[I], VX(FX55) : Store registers from V0 to VX in the main memory, starting at location I.
			Note that X is the number of the register, so we can use it in the loop. 
			In the following pseudo-code, V[i] allows for indexed register access, so that VX == V[X] */
			for (int i = 0; i < instruction.SecondQuarter + 1 && (m_cpu.I + i) < MEM_SIZE; i++)
			{
				m_memory.setByte(m_cpu.I + i, m_cpu.V[i]);
			}

			break;


		case 0x65: // LD VX, [I] (FX65): Load the memory data starting at address I into the registers V0 to VX
			for (int i = 0; i < instruction.SecondQuarter + 1 && (m_cpu.I + i) < MEM_SIZE; i++)
			{
				m_cpu.V[i] = m_memory[m_cpu.I + i];
			}

			break;

		default:
			std::cerr << "Unknown instruction: 0x" << std::hex << static_cast<int>(instruction.FirstQuarter) << static_cast<int>(instruction.SecondQuarter) << static_cast<int>(instruction.ThirdQuarter) << static_cast<int>(instruction.FourthQuarter) << "\n";
			exit(-1);
			break;
		}

		clearBuffer(operator_buffer);
		break;


	default:
		std::cerr << "Unknown instruction: 0x" << std::hex << instruction.FirstQuarter << instruction.SecondQuarter << instruction.ThirdQuarter << instruction.FourthQuarter << "\n";
		exit(-1);
		break;
	}
}