#pragma once

#include "Lexer.h"

#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Interpreter
{
public:
	void Interpret(std::vector<Instruction> program, std::unordered_map<char, uint32_t> labels);

private:
	void RuntimeError(std::string msg, uint32_t instruction)
	{
		std::ostringstream oss;
		oss << "Runtime Error at Instruction " << instruction << ": " << msg << std::endl;
		throw std::runtime_error(oss.str());
		halted = true;
	}

	void RuntimeVariableError(char id, uint32_t instruction)
	{
		std::ostringstream oss;
		oss << "Runtime Error at Instruction " << instruction << ": Variable id " << (int)id << " is undefined.";
		throw std::runtime_error(oss.str());
		halted = true;
	}

	bool halted = false;

	std::unordered_map<char, char> variables;
	std::unordered_map<char, std::vector<char>> internalFuncVars;
	std::vector<uint32_t> funcReturnPoints; // stack for function return points
	std::vector<char>  funcOutDirs;
};