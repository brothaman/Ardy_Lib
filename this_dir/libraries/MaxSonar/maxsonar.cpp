#include <Arduino.h>
#include <maxsonar.h>

#define SOS 343.0

maxsonar::maxsonar( int pin) {
	maxsonar::pw_pin = pin;
	pinMode( maxsonar::pw_pin, INPUT);
}
void maxsonar::updateRange( double * range) {
	*range = pulseIn( maxsonar::pw_pin, HIGH)/1000000.0/2*1000.0*SOS;
}
