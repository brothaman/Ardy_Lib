#include <SPI.h>
#include <Pixy.h>
#include <ContinuousRotationServo.h>
#include <CMU_helper.h>

Pixy pixy;
ContinuousRotationServo Servo;
int distance;

void setup()
{
  Servo.begin(2);
  Serial.begin(9600);
}

void loop()
{
  pix.blocks = pixy.getBlocks();
  pix.x_position = pixy.blocks[0].x-160;
  Serial.print(pix.x_position);
  if(pix.x_position > 15) {
    Servo.rotateLeft( 50, 1);
  } else if(pix.x_position < -15) {
    Servo.rotateRight(50, 1);
  } else {
    Servo.noMovement(1);
  }
}
