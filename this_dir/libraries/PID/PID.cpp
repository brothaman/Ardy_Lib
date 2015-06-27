#include <Arduino.h>
#include <PID.h>

#define TOLERANCE .15

///////////////////////////////////////////////////////////////////////////////
// PID STUFFS
PID::PID( double * Kp, double * Ki, double * Kd,
		double maxinput, double mininput, double maxoutput, double minoutput) {
	PID::_Kp = * Kp;
	PID::_Ki = * Ki;
	PID::_Kd = * Kd;
	PID::lastmillis = millis();
	PID::_maxO = maxoutput;
	PID::_maxI = maxinput;
	PID::_minO = minoutput;
	PID::_minI = mininput;
}

void PID::updateParameters( double * Kp, double * Ki, double * Kd) {
	PID::_Kp = * Kp;
	PID::_Ki = * Ki;
	PID::_Kd = * Kd;
}


void PID::updateValues( const double desiredOutput, const double actualOutput, double * adjvar) {
	//double a = NAN;
	double adder = 0;
	int mm = 0, om = 0;
	//Serial.println(*adjvar);
	PID::eti = (PID::currmillis - PID::lastmillis);
	PID::eti = PID::eti/1000.0;
	//Serial.print("previous time: "); Serial.println(PID::lastmillis);
	PID::lastmillis = PID::currmillis;
	PID::currmillis = millis();
	// DEBUG
	/*
	Serial.print("current time: "); Serial.println(PID::currmillis);
	Serial.print("change in time: "); Serial.println(PID::eti);
	Serial.print("desired output: "); Serial.println(desiredOutput);
	Serial.print("actual output: "); Serial.println(actualOutput);
	// DEBUG
*/
	if(desiredOutput >= 0) { om = 1;}
	else { om = -1;}
	PID::previous_err = PID::err;
	PID::err = ( 
			map( desiredOutput, _minI, _maxI, _minO, _maxO) - 
			map( actualOutput, _minI, _maxI, _minO, _maxO) 
			);
	// DEBUG
	/*
	Serial.print("error is: ");Serial.println(PID::err);
	// DEBUG
	*/ 
	if( abs(actualOutput - desiredOutput) >= TOLERANCE*desiredOutput) {
		if(err > 0) {
			mm = -1;
		} else if (actualOutput - desiredOutput < 0) {
			mm = 1;
		}
	} else {
		mm = 0;
	}
	// logic block to protect the motor from going outside of the max and min value
	//if(*adjvar==a) { 
	//	*adjvar = 0;
	//	Serial.println("HELLO WORLD");
	//}
	PID::cumulative_err = PID::cumulative_err + PID::err;
	adder =  ( PID::P() + PID::I() + PID::D());
	*adjvar = ( *adjvar + adder);//+ mm*( PID::P() + PID::I() + PID::D()) );
	/*
	// DEBUG
	Serial.print("desired output: "); Serial.println( desiredOutput);
	Serial.print("actual output: "); Serial.println( actualOutput);
	Serial.print("Error: "); Serial.println( PID::err);
	Serial.print("Cumulative Error: "); Serial.println(cumulative_err);
	Serial.print("Proportional: ");Serial.println( PID::P());
	Serial.print("Integeral: ");Serial.println( PID::I());
	Serial.print("Differential: ");Serial.println( PID::D());
	Serial.print("Total PID Compensation: ");Serial.println(adder);
	Serial.print("Adjustment variable before limits: ");Serial.println(*adjvar);
	*/
	if(*adjvar >= _maxO) {
		*adjvar = _maxO;
	} else if(*adjvar <= _minO) {
		*adjvar = _minO;
	}
	//Serial.println(*adjvar);
}

double PID::P() {
	// DEBUG
	//Serial.print("Proportional: ");Serial.println(PID::_Kp*PID::err);
	// DEBUG
	return PID::_Kp*PID::err;
}
double PID::I() {
	// DEBUG
	//Serial.print("Integeral: ");Serial.println(PID::_Ki*PID::err*eti);
	// DEBUG
	return PID::_Ki*PID::cumulative_err*PID::eti;
}
double PID::D() {
	// DEBUG
	//Serial.print("Differential: ");Serial.println(PID::_Kd*PID::err/eti);
	// DEBUG
	if(!(eti > 0)) { return 0;}
	return PID::_Kd*(PID::err-PID::previous_err)/PID::eti;
}
