
#include "MorseChar.h"
#include "Morse.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "Arduino.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Morse::Morse()
{
    MCray[0].init('A',".-");
    MCray[1].init('B',"-...");
    MCray[2].init('C',"-.-.");
    MCray[3].init('D',"-..");
    MCray[4].init('E',".");
    MCray[5].init('F',"..-.");
    MCray[6].init('G',"--.");
    MCray[7].init('H',"....");
    MCray[8].init('I',"..");
    MCray[9].init('J',".---");
    MCray[10].init('K',"-.-");
    MCray[11].init('L',".-..");
    MCray[12].init('M',"--");
    MCray[13].init('N',"-.");
    MCray[14].init('O',"---");
    MCray[15].init('P',".--.");
    MCray[16].init('Q',"--.-");
    MCray[17].init('R',".-.");
    MCray[18].init('S',"...");
    MCray[19].init('T',"-");
    MCray[20].init('U',"..-");
    MCray[21].init('V',"...-");
    MCray[22].init('W',".--");
    MCray[23].init('X',"-..-");
    MCray[24].init('Y',"-.--");
    MCray[25].init('Z',"--..");
    MCray[26].init('1',".---");
    MCray[27].init('2',"..---");
    MCray[28].init('3',"...--");
    MCray[29].init('4',"....-");
    MCray[30].init('5',".....");
    MCray[31].init('6',"-....");
    MCray[32].init('7',"--...");
    MCray[33].init('8',"---..");
    MCray[34].init('9',"----.");
    MCray[35].init('0',"-----");
    MCray[36].init('/',"-..-.");
    MCray[37].init('*',".-.-.");
    MCray[38].init('.',".-.-.-");
    MCray[39].init('-',"-....-");
    MCray[40].init(',',"--..--");
    MCray[41].init('?',"..--..");
    MCray[42].init(' '," ");
    MCray[43].init(0,"      ");
}

Morse::~Morse()
{

}


void Morse::sendMessage()
{  
    for(unsigned i=0; i < strlen(icray)+1;i++)
    {  
        for( int j = 0; j < 44; ++j)
        {   
           if( toupper(*(icray+i)) == MCray[j].getChar())
           {
              MCray[j].send();    
              break;
           }   
        }  
    } 

}

void Morse::setMessage(const char *_icray)
{ 
    icray=_icray;
    sendMessage();
}