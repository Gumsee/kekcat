#pragma once

namespace kekcat
{
    extern int  iStepsize;
    extern int  iSaturation;
    extern int  iValue;
    extern bool bTrueColor;
    extern bool bBackground;
    extern bool bInvert;
    extern bool bForceColor;

    struct KEKRGB 
    { 
        const int r, g, b;

        KEKRGB(const int& r, const int& g, const int& b) : r(r), g(g), b(b) {};
        KEKRGB(const int& s)                             : r(s), g(s), b(s) {};
    };

    extern KEKRGB HSVToRGB(float h, float s, float v);
    extern void colorizeLine(const char* line, unsigned long offset);
};