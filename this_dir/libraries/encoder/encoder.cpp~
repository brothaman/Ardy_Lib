#include <Arduino.h>
#include <encoder.h>


///////////////////////////////////////////////////////////////////////////////
// ENCODER STUFFS
encoder::encoder( int pinA, int pinB, int encoderResolution) {
	encoder::_pinA = pinA; encoder::_pinB = pinB;
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	if(encoder::_pinA == 2 || encoder::_pinB == 2) {
		encoder::_ISR = 0;
	} else if( encoder::_pinA == 3 || encoder::_pinB == 3) {
		encoder::_ISR = 1;
	}
}

void encoder::doEncoder() {
	( digitalRead(encoder::_pinA) == digitalRead(encoder::_pinB) ? 
		encoder::clks--:encoder::clks++);
}

float encoder::getRPM() {
	float RPM;
	// revolutions encoderResolution/clks
	detachInterrupt( encoder::_ISR);
	RPM = (encoder::clks/encoder::encoderResolution*
			(1e3/(encoder::lastmillis-millis())));
	encoder::lastmillis = millis();
	encoder::clks = 0;
	return RPM;
}


