#include <Arduino.h>
#include <SPI.h>
#include <Pixy.h>

struct pixy_t {
	uint16_t blocks;
	short int x_position;
	int object_width;
} pix;
