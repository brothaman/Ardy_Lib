#include <Arduino.h>

#ifndef PID_h
#define PID_h

class PID {
	private:
		unsigned long int lastmillis;
		unsigned long int currmillis;
		double P();
		double I();
		double D();
		double _Kp, _Ki, _Kd;
		double err, previous_err, cumulative_err;
		double _maxO, _maxI, _minO, _minI;
		double eti;
	public:
		PID( double * Kp, double * Ki, double * Kd,
				double maxinput, double mininput, double maxoutput, double minoutput);
		void updateParameters( double * Kp, double * Ki, double * Kd);
		void updateValues( double desiredOutput, double actualOutput, double * adjvar);
};
#endif
