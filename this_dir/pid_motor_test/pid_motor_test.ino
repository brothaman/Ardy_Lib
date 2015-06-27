#include <PID.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <ping.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// encoder pins
int right_encoder_pin_a = 2, right_encoder_pin_b = 4, left_encoder_pin_a = 3, left_encoder_pin_b = 5;
int encoder_resolution = 512;
int rightISR = 0, leftISR = 1;
volatile int left_clicks = 0, right_clicks = 0;
unsigned long lastmillis = 0, curmillis = 0, lm = 0, cm = 0;
unsigned int sample = 0;
double et = 0;
// PID parameters


// Constructors
double rki = .001, rkp = .1, rkd = 0, wkp = .1, wki = 0, wkd = 0.00001;
PID left_wheel_pid( &wkp, &wki, &wkd, 500, -500, 255, -255);
PID right_wheel_pid( &wkp, &wki, &wkd, 500, -500, 255, -255);

double drpm = 0, left_actual_rpm = 0, right_actual_rpm = 0, left_motor_volt = 0, right_motor_volt  = 0;
Adafruit_DCMotor *left_motor = AFMS.getMotor(1);
Adafruit_DCMotor *right_motor = AFMS.getMotor(2);

void setup() {  
  // set up for encoders
  pinMode( left_encoder_pin_a, INPUT); pinMode( left_encoder_pin_b, INPUT);
  pinMode( right_encoder_pin_a, INPUT); pinMode( right_encoder_pin_b, INPUT);
  
  // turn on pull up resistors
  digitalWrite( left_encoder_pin_a, HIGH); digitalWrite( left_encoder_pin_b, HIGH);
  digitalWrite( right_encoder_pin_a, HIGH); digitalWrite( right_encoder_pin_b, HIGH);
  
  // set up for motors
  AFMS.begin();
  left_motor->setSpeed(0);
  right_motor->setSpeed(0);
  left_motor->run( RELEASE);
  right_motor->run( RELEASE);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  char buf[4];
  while (Serial.available() != 0) {
    Serial.readBytesUntil('\n', buf, 45);
    drpm = atof(buf);
  }
  
  /////////////////////////////////////////////////////
  detachInterrupt(leftISR); 
  detachInterrupt(rightISR);
  curmillis = cm = millis();
  
  if(cm >= lm + 50) {
    // time management
    //csvoutput();
    et = cm - lm;
    et = et/1000.0/60.0;
    lm = cm;
    //Serial.println("left encoder: "); Serial.print(left_clicks);
    //Serial.println("right encoder: "); Serial.print(right_clicks);
    getRPM(&left_actual_rpm, &left_clicks, encoder_resolution);
    getRPM(&right_actual_rpm, &right_clicks, encoder_resolution);
    
    // pid stuffs
    left_wheel_pid.updateValues( drpm, left_actual_rpm, &left_motor_volt);
    right_wheel_pid.updateValues( drpm, right_actual_rpm, &right_motor_volt);
    sample++;
    debug();
  }
  attachInterrupt( leftISR, doLeftEncoder, CHANGE);
  attachInterrupt( rightISR, doRightEncoder, CHANGE);
  
  if(left_motor_volt > 0) {
    left_motor->run(FORWARD);
  } else {
    left_motor->run(BACKWARD);
  }
  if(right_motor_volt > 0) {
    right_motor->run(FORWARD);
  } else {
    right_motor->run(BACKWARD);
  }
  left_motor->setSpeed(abs(left_motor_volt));
  right_motor->setSpeed(abs(right_motor_volt));
}

void debug() {
  Serial.print("Desired wheel speed: "); Serial.println(drpm);
  Serial.print("Actual left wheel speed: "); Serial.print(left_actual_rpm);
  Serial.print(", Actual right wheel speed: "); Serial.println(right_actual_rpm);
  Serial.print("Left motor voltage: "); Serial.print(left_motor_volt);
  Serial.print(", Right motor voltage: "); Serial.println(right_motor_volt);
}
void csvoutput() {
  Serial.print(sample);
  Serial.print(","); Serial.print(drpm);
  Serial.print(","); Serial.print(left_actual_rpm);
  Serial.print(","); Serial.print(right_actual_rpm);
  Serial.print(","); Serial.print(left_motor_volt);
  Serial.print(","); Serial.println(right_motor_volt);
}
