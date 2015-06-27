#include <Arduino.h>

#ifndef ping_h
#define ping_h

class ping {
	private:
		int pins[2];
		unsigned long pulse;
		boolean threepinping;
	public:
		ping( const int pinA, const int pinB);
void updateRange( double * range);

};

#endif
