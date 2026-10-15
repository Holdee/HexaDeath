#pragma once

#include <vector>
#include <stdexcept>
#include <unordered_map>

struct Instruction
{
	char call;
	std::vector<char> args;
	std::vector<char> outs;
};

class Lexer
{
public:
	std::vector<Instruction> Lex(std::vector<char> code);

	std::unordered_map<char, uint32_t> getLabels()
	{
		return labels;
	}

private:
	bool halted = false;

	std::unordered_map<char, uint32_t> labels;
};