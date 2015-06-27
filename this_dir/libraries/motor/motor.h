#include <Arduino.h>

#ifndef motor_h
#define motor_h

class motor {
	private:
		int _pin;
		int voltage;
	public:
		motor( int pin);
		void setMotorSpeed( int mvolt);
};

#endif
