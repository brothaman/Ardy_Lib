#ifndef Morse_h
#define Morse_h

#include <inttypes.h>
#include "MorseChar.h"

class Morse 
{
public:
    void setMessage(const char* _icray);
    void sendMessage();
    Morse();
    virtual ~Morse();
    MorseChar MCray[45]; 
    const char *icray;
};

#endif