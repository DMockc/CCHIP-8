#include "ProgramManager.h"

#ifndef _DEBUG
#define DEBUG(x)
#endif // DEBUG
#define DEBUG(x) std::cout << x << "\n"

ProgramManager::ProgramManager(chip8cpu& cpu, Memory& mem, DisplayManager& display)
	: m_cpu(cpu), m_memory(mem), m_display(display), m_windowEvent() {}


void ProgramManager::loadProgram(const char* file_path)
{
	if (!checkExtension(file_path))
	{
		std::cerr << " File extension isn't correct!\n";
		return;
	}

	std::ifstream file(file_path, std::ios::binary | std::ios::ate);
	std::pair<char*, size_t> fileContent = loadFileInBuffer(file);

	if (fileContent.first == nullptr)
	{
		std::cerr << "File couldn't be opened!\n";
		return;
	}

	for (size_t i = 0; (RAM_START + i) < MEM_SIZE && i < fileContent.second; i++)
	{
		m_memory.setByte(RAM_START + static_cast<uWord>(i), fileContent.first[i]);
	}

	delete[] fileContent.first;

	m_program_size = static_cast<int>(fileContent.second);

	std::cout << "Program loaded!\n";

	SDL_Delay(1000);
}

void ProgramManager::runProgram()
{
	Instruction actualInstruction;
	bool isRunning = true;
	unsigned int FPS_LIMIT = 500;

	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	while (isRunning)
	{
		unsigned int desiredDelta = 1000 / FPS_LIMIT;
		Uint32 startLoop = SDL_GetTicks();

		if (SDL_PollEvent(&m_windowEvent))
		{
			Keyboard::updateKeymap(m_windowEvent, FPS_LIMIT);

			switch (m_windowEvent.type)
			{
			case SDL_DROPFILE:
				m_cpu.resetCPU();
				m_memory.clearMem();
				m_display.clearDisplay();

				loadProgram(m_windowEvent.drop.file);
				SDL_free(m_windowEvent.drop.file);
				break;

			case SDL_QUIT:
				isRunning = false;
				break;

			default:
				break;
			}
		}

		if (m_program_size == 0) continue; //There isn't a loaded program

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

		m_cpu.updateTimers(FPS_LIMIT);
		m_display.drawMatrix(8);


		SDL_RenderPresent(m_display.renderer);

		/* FPS Limitation */
		Uint32 delta = SDL_GetTicks() - startLoop;
		if (delta < desiredDelta)
		{
			SDL_Delay(desiredDelta - delta);
		}
		
	}
}

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

	uByte xcoord = 0;
	uByte ycoord = 0;

	bool collision = false;

	/* Instructions documentation: https://tonisagrista.com/blog/2021/chip8-spec */

	switch (instruction.FirstQuarter)
	{
	case 0x0:

		switch (instruction.FourthQuarter)
		{

		case CLS:
			SDL_SetRenderDrawColor(m_display.renderer, BLACK);
			SDL_RenderClear(m_display.renderer);
			
			for (int i = 0; i < m_display.HEIGHT; i++)
			{
				for (int j = 0; j < m_display.WIDTH; j++)
				{
					m_display.screenMatrix[i][j] = 0;
				}
			}

			break;


		case RET: 
			m_cpu.PC = m_memory.stack[m_cpu.SP];
			m_cpu.SP--;

			break;


		default:
			UNKNOWN_INSTRUCTION;
			break;
		}

		break;


	case JMP_NNN:
		loadNumberToBuffer(operator_buffer, instruction.SecondQuarter, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.PC = operator_buffer;

		clearBuffer(operator_buffer);
		break;


	case CALL_NNN: 
		m_cpu.SP++;

		m_memory.stack[m_cpu.SP] = m_cpu.PC;

		loadNumberToBuffer(operator_buffer, instruction.SecondQuarter, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.PC = operator_buffer;

		clearBuffer(operator_buffer);
		break;


	case SE_VX_NN:
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);

		if (m_cpu.V[instruction.SecondQuarter] == operator_buffer)
		{
			m_cpu.PC += 2;
		}

		clearBuffer(operator_buffer);
		break;


	case SNE_VX_NN:
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);

		if (m_cpu.V[instruction.SecondQuarter] != operator_buffer)
		{
			m_cpu.PC += 2;
		}

		clearBuffer(operator_buffer);
		break;


	case SE_VX_VY:

		if (m_cpu.V[instruction.SecondQuarter] == m_cpu.V[instruction.ThirdQuarter])
		{
			m_cpu.PC += 2;
		}

		break;


	case LD_VX_NN:
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.V[instruction.SecondQuarter] = static_cast<uByte>(operator_buffer);

		clearBuffer(operator_buffer);
		break;


	case ADD_VX_NN:
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.V[instruction.SecondQuarter] += operator_buffer;

		clearBuffer(operator_buffer);
		break;

	case BITWISE_OP: 
		switch (instruction.FourthQuarter)
		{
		case LD_VX_VY:
			m_cpu.V[instruction.SecondQuarter] = m_cpu.V[instruction.ThirdQuarter];

			break;


		case OR_VX_VY:
			m_cpu.V[instruction.SecondQuarter] |= m_cpu.V[instruction.ThirdQuarter];

			break;


		case AND_VX_VY:
			m_cpu.V[instruction.SecondQuarter] &= m_cpu.V[instruction.ThirdQuarter];

			break;


		case XOR_VX_VY:
			m_cpu.V[instruction.SecondQuarter] ^= m_cpu.V[instruction.ThirdQuarter];

			break;


		case ADD_VX_VY: 
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


		case SUB_VX_VY:
			if (m_cpu.V[instruction.ThirdQuarter] - m_cpu.V[instruction.SecondQuarter] < 0x00)
			{
				m_cpu.V[0xF] = 1;
			}
			else
			{
				m_cpu.V[0xF] = 0;
			}

			m_cpu.V[instruction.SecondQuarter] -= m_cpu.V[instruction.ThirdQuarter];

			break;


		case SHR_VX:

			m_cpu.V[0xF] = m_cpu.V[instruction.SecondQuarter] & 0x01;

			m_cpu.V[instruction.SecondQuarter] >>= 1;

			break;


		case SUBN_VX_VY:
			if (m_cpu.V[instruction.ThirdQuarter] > m_cpu.V[instruction.SecondQuarter])
			{
				m_cpu.V[0xF] = 1;
			}
			else
			{
				m_cpu.V[0xF] = 0;
			}

			m_cpu.V[instruction.SecondQuarter] = m_cpu.V[instruction.ThirdQuarter] - m_cpu.V[instruction.SecondQuarter];

			break;


		case SHL_VX:
			m_cpu.V[0xF] = m_cpu.V[instruction.SecondQuarter] & 0x80;

			m_cpu.V[instruction.SecondQuarter] <<= 1;

			break;


		default:
			UNKNOWN_INSTRUCTION;
			break;
		}

		clearBuffer(operator_buffer);
		break;

	case SNE_VX_VY:

		if (m_cpu.V[instruction.SecondQuarter] != m_cpu.V[instruction.ThirdQuarter])
		{
			m_cpu.PC += 2;
		}

		break;


	case LD_I_NNN:
		loadNumberToBuffer(operator_buffer, instruction.SecondQuarter, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.I = operator_buffer;

		clearBuffer(operator_buffer);
		break;


	case JMP_V0_NNN:
		loadNumberToBuffer(operator_buffer, instruction.SecondQuarter, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.PC = m_cpu.V[0x0] + operator_buffer;

		clearBuffer(operator_buffer);
		break;


	case RND_VX_NN:
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);
		m_cpu.V[instruction.SecondQuarter] = (rand() % 256) & operator_buffer;

		srand(static_cast<unsigned int>(time(NULL)));

		clearBuffer(operator_buffer);
		break;


	case DRW_VX_VY_N:
		xcoord = m_cpu.V[instruction.SecondQuarter] % m_display.WIDTH;
		ycoord = m_cpu.V[instruction.ThirdQuarter] % m_display.HEIGHT;

		m_cpu.V[0xF] = 0;

		for (int row = 0; row < instruction.FourthQuarter; row++)
		{

			uByte y_selectedCoord = (ycoord + row) % m_display.HEIGHT;

			for (int column = 0; column < BITS_IN_A_BYTE; column++)
			{

				uByte x_selectedCoord = (xcoord + column) % m_display.WIDTH;

				operator_buffer = (m_memory[m_cpu.I + row] << column) & 0x80; //Select a bit of the byte

				bool color = (operator_buffer >> 7) & 0x01;

				if (m_display.screenMatrix[y_selectedCoord][x_selectedCoord] == 1 && color == 1)
				{
					m_cpu.V[0xF] = 1; //Update collision
				}

				m_display.screenMatrix[y_selectedCoord][x_selectedCoord] ^= color; //Make XOR in [x, y]

				m_display.coords_buffer.push_back(
					DRW_COORD(
						y_selectedCoord,
						x_selectedCoord,
						m_display.screenMatrix[y_selectedCoord][x_selectedCoord]
					)
				);

				clearBuffer(operator_buffer);

				if (x_selectedCoord >= m_display.WIDTH - 1) //Reach X limit
				{
					break;
				}

			}
			if (y_selectedCoord >= m_display.HEIGHT - 1) //Reach Y limit
			{
				break;
			}
		}

		clearBuffer(operator_buffer);
		break;


	case KEYBOARD_OP: 
		switch (instruction.FourthQuarter)
		{
		case SKP_VX:
			if (Keyboard::isPressed(m_cpu.V[instruction.SecondQuarter]))
			{
				m_cpu.PC += 2;
			}

			break;

		case SKNP_VX:
			if (!Keyboard::isPressed(m_cpu.V[instruction.SecondQuarter]))
			{
				m_cpu.PC += 2;
			}

			break;


		default:
			UNKNOWN_INSTRUCTION;
			break;
		}

		clearBuffer(operator_buffer);
		break;


	case REGISTER_OP:
		loadNumberToBuffer(operator_buffer, instruction.ThirdQuarter, instruction.FourthQuarter);

		switch (operator_buffer)
		{
		case LD_VX_DT:
			m_cpu.V[instruction.SecondQuarter] = m_cpu.DT;

			break;


		case LD_VX_K:
			for (uByte i = 0; i < KEYMAP_SIZE; i++)
			{
				if (Keyboard::isReleased(m_windowEvent, i))
				{
					m_cpu.V[instruction.SecondQuarter] = i;
					m_cpu.PC += 2; //Next instruction
				}
			}

			m_cpu.PC -= 2; //Reload the instruction

			break;


		case LD_DT_VX:
			m_cpu.DT = m_cpu.V[instruction.SecondQuarter];

			break;


		case LD_ST_VX:
			m_cpu.ST = m_cpu.V[instruction.SecondQuarter];

			break;


		case ADD_I_VX:
			m_cpu.I += m_cpu.V[instruction.SecondQuarter];

			break;


		case LD_F_VX: 
			m_cpu.I = m_cpu.V[instruction.SecondQuarter] * FONT_SIZE;

			break;


		case LD_B_VX: 
			m_memory.setByte(m_cpu.I, m_cpu.V[instruction.SecondQuarter] / 100);
			m_memory.setByte(m_cpu.I + 1, (m_cpu.V[instruction.SecondQuarter] - m_memory[m_cpu.I] * 100) / 10);
			m_memory.setByte(m_cpu.I + 2, m_cpu.V[instruction.SecondQuarter] - m_memory[m_cpu.I] * 100 - m_memory[m_cpu.I + 1] * 10);

			break;


		case LD_I_VX: 
			for (int i = 0; i <= instruction.SecondQuarter && (m_cpu.I + i) < MEM_SIZE; i++)
			{
				m_memory.setByte(m_cpu.I + i, m_cpu.V[i]);
			}

			break;


		case LD_VX_I:
			for (int i = 0; i <= instruction.SecondQuarter && (m_cpu.I + i) < MEM_SIZE; i++)
			{
				m_cpu.V[i] = m_memory[m_cpu.I + i];
			}

			break;

		default:
			UNKNOWN_INSTRUCTION;
			break;
		}

		clearBuffer(operator_buffer);
		break;


	default:
		UNKNOWN_INSTRUCTION;
		break;
	}
}