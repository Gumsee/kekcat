#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include "kekcat.h"
#include <sstream>

typedef bool (*argfunc)(void);
void usage();

struct Argument
{
    const char* switchName, *switchNameShort;
    const char* description;
    argfunc func;

    Argument(const char* switchName, const char* switchNameShort, const char* description, argfunc func)
    {
        this->switchName      = switchName;
        this->switchNameShort = switchNameShort;
        this->description     = description;
        this->func            = func;
    };
};


static Argument aAvailableArguments[] = 
{
    Argument("--help",       "-h", "Prints this help menu",                     []() { usage();                    return false; }),
    Argument("--usage",      "-u", "Prints this help menu",                     []() { usage();                    return false; }),
    Argument("--truecolor",  "-t", "Tries to use 24Bit truecolor format",       []() { kekcat::bTrueColor = true;  return true; }),
    Argument("--background", "-b", "Changes only background color",             []() { kekcat::bBackground = true; return true; }),
    Argument("--invert",     "-i", "Inverts text color if --background is set", []() { kekcat::bInvert = true;     return true; }),
    Argument("--force",      "-f", "Forces color on non Terminal stdout",       []() { kekcat::bForceColor = true; return true; }),
};

inline unsigned int numArguments() { return sizeof(aAvailableArguments) / sizeof(Argument); }



static const char* usageStr = 
R"(Usage: kekcat [OPTION(S)] [FILE(S)]

When no files are specified or when the filename is -, stdin is being used.
)";

static const char* examplesStr = 
R"(
    
Examples:
  kekcat foo - bar          Output foo's contents, then stdin, then bar's contents.
  echo "Hellowo" | kekcat   rainbowo

Report bugs at    https://github.com/Gumsee/kekcat/issues
kekcat home page: https://github.com/Gumsee/kekcat/
Pay respect at    https://github.com/busyloop/lolcat/
)";

inline std::string offsetGen(int strLength, int dist = 15)
{
    std::string ret;
    for(int i = 0; i < dist - strLength; i++)
        ret += " ";

    return ret;
}

inline void usage()
{
    unsigned long offset = rand() % 360;
    std::string helpStr = usageStr + std::string("\n");
    for(unsigned int j = 0; j < numArguments(); j++)
    {
        Argument &arg = aAvailableArguments[j];
        helpStr += "    " + std::string(arg.switchNameShort) + ", " + std::string(arg.switchName) + offsetGen(strlen(arg.switchName)) + std::string(arg.description) + "\n";
    }
    helpStr += examplesStr;

    std::string line;
    std::istringstream f(helpStr);
    while(std::getline(f, line))
    {
        kekcat::colorizeLine(line.c_str(), offset);
        offset += kekcat::iStepsize * 2;
        if(offset > 360)
            offset -= 360;
    }
}

inline bool passArguments(char* args[], int cnt, void (*defaultAction)(const char*))
{
    if(cnt <= 1) 
        return true;

    for(int i = 1; i < cnt; i++)
    {
        const char* passedArgStr = args[i];
        bool hitAny = false;

        for(unsigned int j = 0; j < numArguments(); j++)
        {
            Argument &arg = aAvailableArguments[j];
            if(strcmp(passedArgStr, arg.switchName) == 0 || strcmp(passedArgStr, arg.switchNameShort) == 0)
            {
                hitAny = true;
                if(!arg.func())
                    return false;
            }
        }

        if(!hitAny)
        {
            if(passedArgStr[0] == '-')
            {
                std::cerr << "Error: unknown argument: '" << passedArgStr << "'" << std::endl;
                std::cerr << "Try --help for help." << std::endl;
                return false;
            }
            else
            {
                defaultAction(passedArgStr);
            }
        }
    }

    return true;
}