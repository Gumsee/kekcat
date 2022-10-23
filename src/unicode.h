#pragma once
#include <string>
#include <vector>

namespace kekcat 
{
    class unicode
    {
    private:
        std::vector<std::basic_string<char>> vUTF8Chars;

    public:
        unicode();
        unicode(const char* utf8);
        unicode(std::string utf8);

        std::basic_string<char>& operator[](const unsigned int& index);
        std::basic_string<char> operator[](const unsigned int& index) const;
        size_t length() const;
    };
}