#include "Lexer.h"

std::vector<Instruction> Lexer::Lex(std::vector<char> code)
{
    std::vector<Instruction> out;
    int i = 0;
    char num = code.size();
    while (num > 3 && !halted)
    {
        Instruction instruction;
        int outkey = 0; int argkey = 0;

        // First should be Out Key
        outkey = code[num - 1];
        num--;

        // Next is Arg Key
        argkey = code[num - 1];
        num--;

        // Log all outs
        for (int i = 0; i < outkey; i++)
        {
            if (num <= 0) { halted = true; break; } // sends to parser to figure out what went wrong
            instruction.outs.push_back(code[num - 1]);
            num--;
        }

        // Next is call
        if (!halted)
        {
            instruction.call = code[num - 1]; 
            num--;
        }
        else
        {
            instruction.call = 0;
        }

        // Log all args
        for (int i = 0; i < argkey; i++)
        {
            if (num <= 0) { halted = true; break; } // sends to parser to figure out what went wrong
            instruction.args.push_back(code[num - 1]);
            num--;
        }

        if (instruction.call == 17) // locate all labels
        {
            labels.emplace(instruction.args[0], i);
        }

        out.push_back(instruction); // push back
        i++;
    }
    // if num > 0, the parser will catch it.

    return out;
}
