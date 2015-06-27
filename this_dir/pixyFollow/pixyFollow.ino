#include <SPI.h>
#include <PID.h>
#include <Pixy.h>
#include <Servo.h>
#include <CMU_helper.h>
#include <maxsonar.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Pixy pixy;
// junk
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
double attitude = 0;  // how aggressive should the turn be
double akp = 1, aki = 0, akd = 1;
Servo servo;
int distance;
double ckp = .025, cki = 0.001, ckd = .000125;
int right_encoder_pin_a = 2, right_encoder_pin_b = 4, left_encoder_pin_a = 3, left_encoder_pin_b = 5;
int encoder_resolution = 256;
int rightISR = 0, leftISR = 1;
volatile int left_clicks = 0, right_clicks = 0;
unsigned long lastmillis = 0, curmillis = 0, lm = 0, cm = 0;
double et = 0;
double rkp = 1, rki = 0, rkd = 2;
double wkp = .1, wki = 0, wkd = 0.00001;

PID range_pid( &rkp, &rki, &rkd, 0, 4000, 350, -350);
PID left_wheel_pid( &wkp, &wki, &wkd, 350, -350, 255, -255);
PID right_wheel_pid( &wkp, &wki, &wkd, 350, -350, 255, -255);
PID cmu_pid( &ckp, &cki, &ckd, 160, -160, 90, -90);
PID angle_pid( &akp, &aki, &akd, 90, -90, 300, -300);
double drange = 12*25.4, arange;
double left_range, right_range;

maxsonar left_ping(  8);
maxsonar right_ping( 11);
maxsonar front_ping( 12);


void setup()
{
  servo.attach(10);
  Serial.begin(115200);
}

int apos = 0;
double pos = 0;
int count = 0;
int inc = 1;
int dir = 1;

void loop()
{
  pix.blocks = pixy.getBlocks();
  if(!pix.blocks) {
    pan();
  } else {
    follow();
  }
  delay(20);
 
}

void follow() {
  pix.x_position = pixy.blocks[0].x-160;
  cmu_pid.updateValues( 0, pix.x_position, &pos);
  servo.write(pos+90);
  Serial.print("Servo position: "); Serial.println(pos);
  Serial.print("Object position: "); Serial.println(pix.x_position);
}
