#include <Arduino.h>

#ifndef car_h
#define car_h

class car {
	private:
		int left_ping, front_ping, right_ping;
		double left_ping_range, front_ping_range, right_ping_range, 
		double left_wheel_speed, right_wheel_speed;
		volatile int left_wheel_position, right_wheel_position;
		double position[2];
		double camera_angle;
		int camera_turn_speed;
		void turn( int);
		void goforward();
		void gobackward();
	public:
		Search();
		Attack():
} marcellious;

#endif

