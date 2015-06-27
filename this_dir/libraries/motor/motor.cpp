#include <Arduino.h>
#include <motor.h>

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

