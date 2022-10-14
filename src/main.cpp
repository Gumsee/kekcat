#include "kekcat.h"
#include "arguments.h"
#include <cstring>
#include <fstream>
#include <vector>
//#include <sys/ioctl.h>

std::vector<std::string> vFileList;
unsigned long offset;


void colorizeStream(std::istream& stream)
{
    std::string line;
    while(std::getline(stream, line)) 
    {
        kekcat::colorizeLine(line.c_str(), offset);
        offset += kekcat::iStepsize * 2;
        if(offset > 360)
            offset -= 360;
    }
}

int main(int argc, char** argv)
{    
    srand(time(0));

    if(!passArguments(argv, argc, [](const char* filename) {
        //If argument isnt defined, it must be a file
        vFileList.push_back(filename);
    }))
    {
        return 1;
    }

    if(!vFileList.size())
        vFileList.push_back("-");

    /*struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    unsigned short& width = w.ws_col;
    unsigned short& height = w.ws_row;*/

    //std::cout << "WindowSize:" << width << "x" << height << std::endl;


    offset = rand() % 360;

    for(unsigned long i = 0; i < vFileList.size(); i++)
    {
        std::string &filename = vFileList[i];
        //std::istream &activeStream =  == "-" ? std::cin : ;

        if(filename == "-")
        {
            colorizeStream(std::cin);
        }
        else
        {
            std::ifstream file(filename);
            if(!file)
            {
                std::cerr << "kekcat: " << filename << ": No such file or directory" << std::endl;
            }
            colorizeStream(file);
            file.close();
        }
    }
    return 0;
}