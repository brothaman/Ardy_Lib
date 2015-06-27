#include <Arduino.h>

#ifndef maxsonar_h
#define maxsonar_h

class maxsonar {
	private:
		int pw_pin;
	public:
		maxsonar( int);
		void updateRange( double*);
};

#endif
