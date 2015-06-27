#include <Arduino.h>

#ifndef encoder_h
#define encoder_h

class encoder {
	private:
		int _pinA, _pinB;
		volatile int clks;
		unsigned int encoderResolution;
		unsigned long int lastmillis;
	public:
		int _ISR;
		encoder(int pintA, int pinB, int encoderResolution);	
		void doEncoder();
		float getRPM();
};
#endif
