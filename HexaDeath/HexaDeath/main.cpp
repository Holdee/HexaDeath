#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <filesystem>

#include "Numberizer.h"
#include "Lexer.h"
#include "Interpreter.h"
#include "Parser.h"

const char* VERSION = "1.0.0";

void PrintHelp()
{
	std::cout << "HexaDeath (hxd) version " << VERSION << "\n"
		<< "Copyright 2026 Holden Cook\n\n"
		<< "Usage: hxd (Filename) [Options] [Parameters]\n\n"
		<< "Options:\n"
		<< "\t--help: Prints this help message.\n"
		<< "\t--version: Prints program version.\n"
		<< "Parameters:\n"
		<< "\t--info: Prints file info (line count, instruction count, etc.)\n"
		<< "\t--norun: Numberizes, Lexes, and Parses file but doesn't execute.\n";
}

int main(int argc, char *argv[])
{
	try
	{
		std::string line;

		if (argc == 1)
		{
			throw std::runtime_error("Error: No input! Type 'hxd --help' for help.");
			return 1;
		}

		std::string firstArg = argv[1]; // first arg

		if (firstArg == "--help")
		{
			PrintHelp();
			return 0;
		}
		else if (firstArg == "--version")
		{
			std::cout << "Version " << VERSION << "\n";
			return 0;
		}

		std::vector<char> numbers;

		std::string fileName = firstArg;

		std::ifstream file(fileName);
		if (!file.is_open()) throw std::runtime_error("Error: Couldn't open file!");

		if (std::filesystem::path(fileName).extension() != ".hexd")
		{
			throw std::runtime_error("Error: File given is not a '.hexd' file.");
		}

		bool norun = false; // Numberizes, Lexes, and Parses but doesn't execute
		bool printinfo = false;

		// Check for any more args
		if (argc > 2)
		{
			for (int i = 2; i < argc; i++)
			{
				std::string arg = argv[i];

				if (arg == "--norun")
				{
					norun = true;
				}
				else if (arg == "--info")
				{
					printinfo = true;
				}
				else
				{
					throw std::runtime_error("Unrecognized argument. Type 'hxd --help' for more info.");
				}
			}
		}

		Numberizer numberizer;
		Lexer lexer;
		Interpreter interpreter;
		Parser parser;

		uint32_t linecnt = 0;

		if (printinfo) std::cout << fileName << " info:\n";

		while (std::getline(file, line))
		{
			std::vector<char> numberized = numberizer.Numberize(line);
			numbers.insert(numbers.end(), numberized.begin(), numberized.end());
			linecnt++;
		}

		if (printinfo) std::cout << "\tHex count: " << numbers.size() << "\n";

		if (printinfo) std::cout << "\tLine count: " << linecnt << "\n";

		std::vector<Instruction> lexed = lexer.Lex(numbers);

		if (printinfo) std::cout << "\tInstruction count: " << lexed.size() << "\n";

		if (!printinfo)
		{
			parser.ParseForErrors(lexed); // check for grammar errors

			if (!norun) interpreter.Interpret(lexed, lexer.getLabels());
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}

	return 0;
}