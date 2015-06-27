#include <Morse.h>
#include <MorseChar.h>

/* Beacon*/

void setup()
{               
     // initialize the digital pin as an output.
     // Pin 13 has an LED connected on most Arduino boards:
     pinMode(13, OUTPUT);   
     Serial.begin(9600);
}

Morse MorseMessage;

void loop()
{
     MorseMessage.setMessage("YO MAMA");
     Serial.print(MorseMessage.MCray);
     delay(1000); 
}
