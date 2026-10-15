#pragma once

#include <vector>
#include <string>
#include <stdexcept>

class Numberizer
{
public:
	std::vector<char> Numberize(std::string line);

private:
	int HexToNumber(char hex);
	bool isHex(char hex);
};