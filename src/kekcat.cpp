#include "kekcat.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>

namespace kekcat
{
    int iStepsize    = 4;
    int iSaturation  = 80;
    int iValue       = 100;
    bool bTrueColor  = false;
    bool bBackground = false;
    bool bInvert     = false;
    bool bForceColor = false;

    KEKRGB HSVToRGB(float h, float s, float v)
    {
        s /= 100.0f;
        v /= 100.0f;

        if(s <= 0.0f)  { return KEKRGB(v); }
        while(h >= 360.0f) { h -= 360.0f; };
        while(h < 0.0f)    { h += 360.0f; };
        h /= 60.0f;
        float ff = h - (int)h;
        float p = v * (1.0f - s);
        float q = v * (1.0f - (s * ff));
        float t = v * (1.0f - (s * (1.0f - ff)));

        switch((int)h) 
        { 
            case 0:  return KEKRGB(v * 255, t * 255, p * 255);
            case 1:  return KEKRGB(q * 255, v * 255, p * 255);
            case 2:  return KEKRGB(p * 255, v * 255, t * 255);
            case 3:  return KEKRGB(p * 255, q * 255, v * 255);
            case 4:  return KEKRGB(t * 255, p * 255, v * 255);
            default: return KEKRGB(v * 255, p * 255, q * 255);
        }
    }

    void colorizeLine(const char* line, unsigned long offset)
    {
        for(unsigned long column = 0; column < strlen(line); column++)
        {
            const char c = line[column];
            KEKRGB color = HSVToRGB(offset + (column * iStepsize), iSaturation, iValue);
            KEKRGB invertedcolor = KEKRGB(255 - color.r, 255 - color.g, 255 - color.b);
            
            //Only output color if stdout is a Terminal, or if its being forced
            if(isatty(fileno(stdout)) || bForceColor)
            {
                //Background Color
                if(bBackground) 
                    printf("\033[48;2;%d;%d;%dm", color.r, color.g, color.b);

                //Text Color
                if(bInvert && bBackground)
                    printf("\033[38;2;%d;%d;%dm", invertedcolor.r, invertedcolor.g, invertedcolor.b); 
                else if(!bBackground)
                    printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
            }

            //Text
            printf("%c", c);
        }

        //Colorreset
        if(isatty(fileno(stdout)) || bForceColor)
            printf("\033[0m");
        printf("\n");
    }
};