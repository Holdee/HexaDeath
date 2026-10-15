#include "Parser.h"

bool Parser::ParseForErrors(std::vector<Instruction> instructions)
{
    uint32_t i = 0;
    for (Instruction ins : instructions)
    {
        LegalArgOut legal = LEGALS[ins.call]; // get the legal arg in and outs for the call

        if (legal.argCnt != ins.args.size())
        {
            ParserErrorArg(ins.call, ins.args.size(), i);
            return false;
        }
        if (legal.outCnt != ins.outs.size())
        {
            ParserErrorOut(ins.call, ins.outs.size(), i);
            return false;
        }
        i++;
    }
    return true;
}
