#include "Interpreter.h"

void Interpreter::Interpret(std::vector<Instruction> program, std::unordered_map<char, uint32_t> labels)
{
	Instruction ins;
	for (uint32_t i = 0; i < program.size(); i++)
	{
		if (halted)
			break;

		ins = program[i];

		switch (ins.call)
		{
		case 0: // NULL
			break;
		case 1: // NEW VAR
		{
			variables.emplace(ins.args[0], 0);
			break;
		}
		case 2: // ASSIGN VAR
		{
			char id = ins.outs[0];
			auto it = variables.find(id);
			if (it != variables.end())
			{
				it->second = ins.args[0]; // assign
			}
			else
			{
				RuntimeVariableError(id, i);
			}
			break;
		}
		case 3: // INC VAR
		{
			char id = ins.args[0];
			auto it = variables.find(id);
			if (it != variables.end())
			{
				it->second++; // assign
			}
			else
			{
				RuntimeVariableError(id, i);
			}
			break;
		}
		case 4: // DEC VAR
		{
			char id = ins.args[0];
			auto it = variables.find(id);
			if (it != variables.end())
			{
				it->second--;
			}
			else
			{
				RuntimeVariableError(id, i);
			}
			break;
		}
		case 5: // PRINT VALUE
		{
			std::cout << ins.args[0];
			break;
		}
		case 6: // PRINT VAR
		{
			char id = ins.args[0];
			auto it = variables.find(id);
			if (it != variables.end())
			{
				std::cout << it->second;
			}
			else
			{
				RuntimeVariableError(id, i);
			}
			break;
		}
		case 7: // INPUT TO VAR
		{
			char id = ins.outs[0];
			auto it = variables.find(id);

			if (it != variables.end())
			{
				std::cin >> it->second;
			}
			else
			{
				RuntimeVariableError(id, i);
			}
			break;
		}
		case 8: // VAR == VAL
		{
			char id1 = ins.args[1];
			auto it1 = variables.find(id1);

			char id2 = ins.outs[0];
			auto it2 = variables.find(id2);

			if (it1 != variables.end() && it2 != variables.end())
			{
				it2->second = it1->second == ins.args[0];
			}
			else
			{
				if (it1 == variables.end()) RuntimeVariableError(id1, i);
				if (it2 == variables.end()) RuntimeVariableError(id2, i);
			}
			break;
		}
		case 9: // VAR == VAR
		{
			char id1 = ins.args[1];
			auto it1 = variables.find(id1);

			char id2 = ins.args[0];
			auto it2 = variables.find(id2);

			char id3 = ins.outs[0];
			auto it3 = variables.find(id3);

			if (it1 != variables.end() && it2 != variables.end() && it2 != variables.end())
			{
				it3->second = it1->second == it2->second;
			}
			else
			{
				if (it1 == variables.end()) RuntimeVariableError(id1, i);
				if (it2 == variables.end()) RuntimeVariableError(id2, i);
				if (it3 == variables.end()) RuntimeVariableError(id3, i);
			}
			break;
		}
		case 10: // VAR > VAL
		{
			char id1 = ins.args[1];
			auto it1 = variables.find(id1);

			char id2 = ins.outs[0];
			auto it2 = variables.find(id2);

			if (it1 != variables.end() && it2 != variables.end())
			{
				it2->second = it1->second > ins.args[0];
			}
			else
			{
				if (it1 == variables.end()) RuntimeVariableError(id1, i);
				if (it2 == variables.end()) RuntimeVariableError(id2, i);
			}
			break;
		}
		case 11: // VAR > VAR
		{
			char id1 = ins.args[1];
			auto it1 = variables.find(id1);

			char id2 = ins.args[0];
			auto it2 = variables.find(id2);

			char id3 = ins.outs[0];
			auto it3 = variables.find(id3);

			if (it1 != variables.end() && it2 != variables.end() && it2 != variables.end())
			{
				it3->second = it1->second > it2->second;
			}
			else
			{
				if (it1 == variables.end()) RuntimeVariableError(id1, i);
				if (it2 == variables.end()) RuntimeVariableError(id2, i);
				if (it3 == variables.end()) RuntimeVariableError(id3, i);
			}
			break;
		}
		case 12: // VAR < VAL
		{
			char id1 = ins.args[1];
			auto it1 = variables.find(id1);

			char id2 = ins.outs[0];
			auto it2 = variables.find(id2);

			if (it1 != variables.end() && it2 != variables.end())
			{
				it2->second = it1->second < ins.args[0];
			}
			else
			{
				if (it1 == variables.end()) RuntimeVariableError(id1, i);
				if (it2 == variables.end()) RuntimeVariableError(id2, i);
			}
			break;
		}
		case 13: // VAR < VAR
		{
			char id1 = ins.args[1];
			auto it1 = variables.find(id1);

			char id2 = ins.args[0];
			auto it2 = variables.find(id2);

			char id3 = ins.outs[0];
			auto it3 = variables.find(id3);

			if (it1 != variables.end() && it2 != variables.end() && it2 != variables.end())
			{
				it3->second = it1->second < it2->second;
			}
			else
			{
				if (it1 == variables.end()) RuntimeVariableError(id1, i);
				if (it2 == variables.end()) RuntimeVariableError(id2, i);
				if (it3== variables.end()) RuntimeVariableError(id3, i);
			}
			break;
		}
		case 14: // JUMP
		{
			char id = ins.args[0];
			auto it = labels.find(id);
			if (it != labels.end())
			{
				i = it->second;
			}
			else
			{
				RuntimeError("Label undefined.", i);
			}
			break;
		}
		case 15: // JUMP IF NOT 0
		{
			char id1 = ins.args[0]; // label id
			auto it1 = labels.find(id1);
			char id2 = ins.args[1]; // var
			auto it2 = variables.find(id2);
			if (it1 != labels.end() && it2 != variables.end())
			{
				if (it2->second != 0)
					i = it1->second;
			}
			else
			{
				if (it1 == labels.end())
					RuntimeError("Label undefined.", i);
				if (it2 == variables.end())
					RuntimeVariableError(id2, i);
			}
			break;
		}
		case 16: // JUMP IF 0
		{
			char id1 = ins.args[0]; // label id
			auto it1 = labels.find(id1);
			char id2 = ins.args[1]; // var
			auto it2 = variables.find(id2);
			if (it1 != labels.end() && it2 != variables.end())
			{
				if (it2->second == 0)
					i = it1->second;
			}
			else
			{
				if (it1 == labels.end())
					RuntimeError("Label undefined.", i);
				if (it2 == variables.end())
					RuntimeVariableError(id2, i);
			}
			break;
		}
		case 17: // NEW LABEL
		{
			labels.emplace(ins.args[0], i);
			break;
		}
		}
	}
}
