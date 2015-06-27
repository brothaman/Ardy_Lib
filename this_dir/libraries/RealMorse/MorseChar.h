
#ifndef MorseChar_h
#define MorseChar_h

#include <inttypes.h>

class MorseChar 
{
public:
    void init(char ichar,const char* _icray); 
    char getChar();
    void send();
    MorseChar();
    virtual ~MorseChar();
    const char *icray;
    char ichar;
};

#endif