#include "Numberizer.h"

std::vector<char> Numberizer::Numberize(std::string line)
{
    char c;
    std::vector<char> output;
    
    for (uint32_t i = 0; i < line.length(); i++)
    {
        c = line.at(i);

        if (c == ' ' || c == '\n') // whitespaces & newlines
        {
            continue;
        }
        else if (c == '"') // comments
        {
            if (i == line.length()) throw std::runtime_error("Comment never closed!");
            i++;
            while (i < line.length() && line.at(i) != '"')
            {
                i++;
            }

            if (i >= line.length()) throw std::runtime_error("Comment never closed!");
            continue;
        }
        else if (isHex(c))
        {
            if (i >= line.length()) throw std::runtime_error("No one digit hex values allowed.");
            if (!isHex(line.at(i + 1))) throw std::runtime_error("No one digit hex values allowed.");

            int first = HexToNumber(line.at(i));
            i++;
            int second = HexToNumber(line.at(i));
            char finalnumber = 0;

            finalnumber = (first * 16) + second;
            output.push_back(finalnumber);
        }
        
    }
    return output;
}

int Numberizer::HexToNumber(char hex)
{
    switch (hex)
    {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    default:
        throw std::runtime_error("Numberizer Error: Invalid hexedecimal character!");
    }
}

bool Numberizer::isHex(char hex)
{
    switch(hex)
    {
    case '0': return true;
    case '1': return true;
    case '2': return true;
    case '3': return true;
    case '4': return true;
    case '5': return true;
    case '6': return true;
    case '7': return true;
    case '8': return true;
    case '9': return true;
    case 'A': return true;
    case 'B': return true;
    case 'C': return true;
    case 'D': return true;
    case 'E': return true;
    case 'F': return true;
    }
    return false;
}
