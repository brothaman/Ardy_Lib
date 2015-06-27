#include <Arduino.h>
#ifndef Morse_h
#define Morse_h

class Morse {
	private:
		struct Cypher {
			char letter;
			char * morse;
		};
		void initiateLib();
		char * eval(char c);
		void dot();
		void dash();
		void space();
		struct Cypher cycon[45];
		int pin;
	public:
		Morse(int p);
		void sendMessage(char * str);
};

#endif 
