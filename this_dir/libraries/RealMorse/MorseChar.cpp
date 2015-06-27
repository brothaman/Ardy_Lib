#include "Morse.h"
#include "MorseChar.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "Arduino.h"

#define wpm 8
#define __pin 13
#define dot_len 1200/wpm
#define dot digitalWrite(__pin,HIGH);delay(dot_len);digitalWrite(__pin,LOW);delay(dot_len)
#define dash digitalWrite(__pin,HIGH); delay(3*dot_len);digitalWrite(__pin,LOW);delay(dot_len)
#define space digitalWrite(__pin,LOW);delay(2*dot_len)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MorseChar::MorseChar()
{
 
}

MorseChar::~MorseChar()
{

}

void MorseChar::send()
{
    const char* p=icray;
    while(*p)
    {
        if(*p == '.')
        {
           dot;
        }
        else if(*p == '-')
        {
           dash;
        }
        else
        {
           space;
        }
        p++;  
    }
    space; 
}

char MorseChar::getChar()
{
    return ichar;
}

void MorseChar::init(char ichar,const char *_icray)
{
    icray=_icray;
    this->ichar = ichar; 
}