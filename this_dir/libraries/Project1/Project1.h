#include <Arduino.h>

#ifndef Project1_h
#define Project1_h

class encoder {
	private:
		static int _pinA, _pinB;
		static volatile int clks;
		static int _ISR;
		static unsigned int encoderResolution;
		static unsigned long int lastmillis;
	public:
		encoder(int pintA, int pinB, int encoderResolution);	
		static void doEncoder();
		static float getRPM();
};
/*
class motor {
	private:
		int _pin;
		int voltage;
	public:
		motor( int pin);
		void setMotorSpeed( int mvolt);
};

class PID {
	private:
		unsigned long int lastmillis;
		double P();
		double I();
		double D();
		double _Kp, _Ki, _Kd;
		double err;
		unsigned int eti;
	public:
		PID( double & Kp, double & Ki, double & Kd);
		void updateParameters( double & Kp, double & Ki, double & Kd);
		void updateValues( double desiredOutput, double actualOutput, double & adjvar);
};
*/
#endif
