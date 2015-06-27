#include <Arduino.h>
#include <Project1.h>

#define TOLERANCE .15


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
	attachInterrupt( encoder::_ISR, doEncoder, CHANGE);
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
	attachInterrupt( encoder::_ISR, encoder::doEncoder, CHANGE);
	return RPM;
}

/*
///////////////////////////////////////////////////////////////////////////////
// MOTOR STUFFS
motor::motor( int pin) {
	motor::_pin = pin;
	pinMode(pin, OUTPUT);
	motor::voltage = 0;
}

void motor::setMotorSpeed( int mvolt) {
	motor::voltage = mvolt;
	digitalWrite( motor::_pin, motor::voltage);
}


///////////////////////////////////////////////////////////////////////////////
// PID STUFFS
PID::PID( double & Kp, double & Ki, double & Kd) {
	PID::_Kp = * Kp;
	PID::_Ki = * Ki;
	PID::_Kd = * Kd;
	PID::lastmillis = millis();
}

void updateParamters( double & Kp, double & Ki, double & Kd) {
	PID::_Kp = * Kp;
	PID::_Ki = * Ki;
	PID::_Kd = * Kd;
}


void updateValues( double desiredOutput, double actualOutput, double & adjvar) {
	int mm = 0;
	PID::eti = PID::lastmillis - millis();
	PID::err = abs( desiredOutput - actualOutput);
	if( desiredOutput - actualOutput <= TOLERANCE*desiredOutput) {
		mm = 1;
	} else if (desiredOutput-actualOutput > TOLERANCE*desiredOutput) {
		mm = -1;
	} else {
		mm = 0;
	}
	*adjvar = ( *adjvar + mm*( PID::P() + PID::I() + PID::D()) );
	PID::lastmillis = millis();
}

double PID::P() {
	return PID::_Kp*PID::err;
}
double PID::I() {
	return PID::_Ki*PID::err*eti;
}
double PID::D() {
	return PID::_Kd*PID::err/eti;
}
*/
