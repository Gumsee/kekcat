#include "unicode.h"
#include <codecvt>
#include <cstdint>
#include <locale>
#include <string>

namespace kekcat 
{
    unicode::unicode() { }
    unicode::unicode(const char* utf8) : unicode(std::string(utf8)) { }

    unicode::unicode(std::string utf8)
    {
        int numBytes = 0;
        for(size_t i = 0L; i < utf8.length();)
        {
            char c = utf8[i];
            if      ((c & 0x80) == 0x00) numBytes = 1; // 1 Octet  (ASCII)
            else if ((c & 0xE0) == 0xC0) numBytes = 2; // 2 Octet
            else if ((c & 0xF0) == 0xE0) numBytes = 3; // 3 Octet
            else if ((c & 0xF8) == 0xF0) numBytes = 4; // 4 Octet
            vUTF8Chars.push_back(utf8.substr(i, numBytes));

            i += numBytes;
        }
    }


    std::basic_string<char>& unicode::operator[](const unsigned int& index)      { return vUTF8Chars[index]; }
    std::basic_string<char> unicode::operator[](const unsigned int& index) const { return vUTF8Chars[index]; }
    size_t unicode::length() const                                               { return vUTF8Chars.size(); }
}