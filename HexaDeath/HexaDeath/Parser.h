#pragma once

#include <vector>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include "Lexer.h"

struct LegalArgOut
{
	int argCnt = 0;
	int outCnt = 0;
};

class Parser
{
public:
	bool ParseForErrors(std::vector<Instruction> instructions);

private:
	bool ParserErrorArg(char call, char illegalArgCnt, uint32_t ins)
	{
		int overunder = illegalArgCnt - LEGALS[call].argCnt;
		std::ostringstream oss;
		if (overunder > 0)
			oss << "Parser Error at instruction " << ins << ": Argument count for function call " << (int)call << " is " << overunder << " over legal argument count.";
		else
			oss << "Parser Error at instruction " << ins << ": Argument count for function call " << (int)call << " is " << -overunder << " under legal argument count.";
		throw std::runtime_error(oss.str().c_str());
	}

	bool ParserErrorOut(char call, char illegalOutCnt, uint32_t ins)
	{
		int overunder = illegalOutCnt - LEGALS[call].outCnt;
		std::ostringstream oss;
		if (overunder > 0)
			oss << "Parser Error at instruction " << ins << ": Output count for function call " << (int)call << " is " << overunder << " over legal output count.";
		else
			oss << "Parser Error at instruction " << ins << ": Output count for function call " << (int)call << " is " << -overunder << " under legal output count.";
		throw std::runtime_error(oss.str().c_str());
	}

	const std::vector<LegalArgOut> LEGALS =
	{
		{0, 0}, // NULL
		{1, 0}, // NEW VAR
		{1, 1}, // ASSIGN VAR
		{1, 0}, // INC VAR
		{1, 0}, // DEC VAR
		{1, 0}, // PRINT VALUE
		{1, 0}, // PRINT VAR
		{0, 1}, // INPUT TO VAR
		{2, 1}, // VAR == VAL
		{2, 1}, // VAR == VAR
		{2, 1}, // VAR > VAL
		{2, 1}, // VAR > VAR
		{2, 1}, // VAR < VAL
		{2, 1}, // VAR < VAR
		{1, 0}, // JUMP
		{2, 0}, // JUMP IF NOT 0
		{2, 0}, // JUMP IF 0
		{1, 0}, // NEW LABEL
	};
};