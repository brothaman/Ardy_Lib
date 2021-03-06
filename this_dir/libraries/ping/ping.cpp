#include <Arduino.h>
#include <ping.h>

#define SOS 343 // speed of sound

ping::ping( const int pinA, const int pinB) {
	ping::pins[0] = pinA;
	ping::pins[1] = pinB;
	ping::threepinping = (ping::pins[1] == 0 ? true:false);
}

void ping::updateRange( double * range) {
	if(threepinping == true) {
		// send signal
		pinMode( pins[0], OUTPUT);
		digitalWrite( pins[0], LOW);
		delayMicroseconds(2);
		digitalWrite( pins[0], HIGH);
		delayMicroseconds(10);
		digitalWrite( pins[0], LOW);
		// wait for signal
		pinMode( pins[0], INPUT);
		pulse = pulseIn( pins[0], HIGH);
		*range = pulse*SOS/1000000.0/2*1000;
		//
	} else {
		// send signal
		pinMode( pins[0],  INPUT);
		pinMode( pins[1], OUTPUT);
		//
		digitalWrite( pins[1], LOW);
		delayMicroseconds(2);
		digitalWrite( pins[1], HIGH);
		delayMicroseconds(10);
		digitalWrite( pins[1], LOW);
		// wait for signal
		pinMode( pins[0], INPUT);
		pulse = pulseIn( pins[0], HIGH);
		*range = pulse*SOS/1000000.0/2*1000;
	}
}
