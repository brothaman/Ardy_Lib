#include <SPI.h>
#include <Pixy.h>
#include <Servo.h>
#include <CMU_helper.h>
#include <maxsonar.h>
#include <PID.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


#define RANGEF 12
// start up function
void start();
boolean start_bool = false;

// declare functions
void Attack();
void obstacle_avoidance();
void Search();
void goforward();
void gobackward();
void turn();

// call class constructors
Pixy pixy;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Servo servo;

// car stuff
double attitude = 0;  // how aggressive should the turn be
double akp = .01, aki = 0, akd = 0;
double actual_servo_angle, desired_servo_angle = 0;
int dir = 1;
int dirt = 1;
int zadir = 1;
int ck = 0;

// pixy camera
double ckp = .0325, cki = 0.001, ckd = .000125;
int apos = 0;
double pos = 0;


// encoder pins
int right_encoder_pin_a = 2, right_encoder_pin_b = 4, left_encoder_pin_a = 3, left_encoder_pin_b = 5;
int encoder_resolution = 512;
int rightISR = 0, leftISR = 1;
volatile int left_clicks = 0, right_clicks = 0;
unsigned long lastmillis = 0, curmillis = 0, lm = 0, cm = 0;
double et = 0;

// PID parameters
double rkp = 1, rki = 0, rkd = 2;
double wkp = .4, wki = 0, wkd = 0.0001;

// Constructors
PID range_pid( &rkp, &rki, &rkd, 0, 4000, 350, -350);
PID left_wheel_pid( &wkp, &wki, &wkd, 350, -350, 255, -255);
PID right_wheel_pid( &wkp, &wki, &wkd, 350, -350, 255, -255);
PID cmu_pid( &ckp, &cki, &ckd, 160, -160, 90, -90);
PID angle_pid( &akp, &aki, &akd, 90, -90, 300, -300);
// setup pid for car to turn and set servo angle to 0

// motor stuffs
Adafruit_DCMotor *left_motor = AFMS.getMotor(1);
Adafruit_DCMotor *right_motor = AFMS.getMotor(2);
double left_desired_rpm = 0, right_desired_rpm = 0, car_speed = 0;
double left_actual_rpm = 0, right_actual_rpm = 0;
double left_motor_volt = 0, right_motor_volt  = 0;

// ping stuffs
double drange = 12*25.4, front_range;
double left_range, right_range;
maxsonar left_ping(  7);
maxsonar right_ping( 11);
maxsonar front_ping( 8);


void setup() {  
  // Servo set up
  servo.attach( 10);
  
  // set up for encoders
  pinMode( left_encoder_pin_a, INPUT); pinMode( left_encoder_pin_b, INPUT);
  pinMode( right_encoder_pin_a, INPUT); pinMode( right_encoder_pin_b, INPUT);
  
  // turn on pull up resistors
  digitalWrite( left_encoder_pin_a, HIGH); digitalWrite( left_encoder_pin_b, HIGH);
  digitalWrite( right_encoder_pin_a, HIGH); digitalWrite( right_encoder_pin_b, HIGH);
  attachInterrupt( leftISR, doLeftEncoder, CHANGE);
  attachInterrupt( rightISR, doRightEncoder, CHANGE);
  
  // set up for motors
  AFMS.begin();
  left_motor->setSpeed(0);
  right_motor->setSpeed(0);
  left_motor->run( RELEASE);
  right_motor->run( RELEASE);
  Serial.begin(115200);
}

void loop() {
  // before every use of millis or the serial ports or delays the 
  detachInterrupt(leftISR); 
  detachInterrupt(rightISR);
  // all code using the millis function goes hear
  // Serial.println(left_clicks);
  curmillis = cm = millis();
  //pix.blocks = pixy.getBlocks();
  if(cm >= lm + 23) {
    // this block occurs every 20ms
    et = cm - lm;
    et = et/1000.0/60.0;
    lm = cm;
    if(start_bool) {
      //Serial.println("Other task");
      pix.blocks = pixy.getBlocks();
      if(pix.blocks) {
        // object found
        //Serial.println("Found!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        Attack();
      } else {
        // find object
        // stop();
        Search();
        //Serial.println("searching");
      }
    } else {
      attachInterrupt( leftISR, doLeftEncoder, CHANGE);
      attachInterrupt( rightISR, doRightEncoder, CHANGE);
      //Serial.println("Starting");
      left_ping.updateRange( &left_range);
      right_ping.updateRange( &right_range);
      front_ping.updateRange( &front_range);
      //debug();
      start();
      //zero_angle_turn(90);
      //delay(1000);
      //zero_angle_turn(-180);
      //delay(1000);
      detachInterrupt(leftISR); 
      detachInterrupt(rightISR);
      // start();
    }
    //debug();
    
    // caluclate speed and motor volts
    getRPM(&left_actual_rpm, &left_clicks, encoder_resolution);
    getRPM(&right_actual_rpm, &right_clicks, encoder_resolution);
    left_wheel_pid.updateValues( left_desired_rpm, left_actual_rpm, &left_motor_volt);
    right_wheel_pid.updateValues( right_desired_rpm, right_actual_rpm, &right_motor_volt);
  }
  // after the millis, delay or serial port are used the isr need to be re-attached
  attachInterrupt( leftISR, doLeftEncoder, CHANGE);
  attachInterrupt( rightISR, doRightEncoder, CHANGE);
  
  // assign motor speeds
  if(left_motor_volt > 0) {
    //Serial.println("Forward  ");
    left_motor->run(FORWARD);
  } else {
    //Serial.println("Backward  ");
    left_motor->run(BACKWARD);
  }
  if(right_motor_volt > 0) {
    right_motor->run(FORWARD);
  } else {
    right_motor->run(BACKWARD);
  }
  left_motor->setSpeed(abs(left_motor_volt));
  right_motor->setSpeed(abs(right_motor_volt));
  //debug();
}

// debug script is written to aid in print statements which will help with error proofing the system
void debug() {
  Serial.print("Front Range: "); Serial.println(front_range, 4);
  Serial.print("Left Range: "); Serial.println(left_range, 4);
  Serial.print("Right Range: "); Serial.println(right_range, 4);
  Serial.print("Desired Range: "); Serial.println(drange, 4);
  Serial.print("Desired left wheel speed: "); Serial.println(left_desired_rpm);
  Serial.print("Desired right wheel speed: "); Serial.println(right_desired_rpm);
  Serial.print("Actual left wheel speed: "); Serial.print(left_actual_rpm);
  Serial.print(", Actual right wheel speed: "); Serial.println(right_actual_rpm);
  Serial.print("Left motor voltage: "); Serial.print(left_motor_volt);
  Serial.print(", Right motor voltage: "); Serial.println(right_motor_volt);
  Serial.print("Object Position: "); Serial.println(pix.x_position);
  Serial.print("Servo angle: "); Serial.println(servo.read());
  Serial.print("Turn attitude: "); Serial.println(attitude);
}

// update the pixy cam's variable with new data about object
void updatePix() {
  pix.blocks = pixy.getBlocks();
  pix.x_position = pixy.blocks[0].x-160;
}

// deprecated function used to stop 12 inches before wall/object
void twelve_inch_stop_pid() {
  getRPM(&left_actual_rpm, &left_clicks, encoder_resolution);
  getRPM(&right_actual_rpm, &right_clicks, encoder_resolution);
  // pid stuffs
  front_ping.updateRange( &front_range);
  if(front_range >= 14*25.4) {
    drange = 14*25.4;
    curmillis = lastmillis;
  } else if( front_range <= 10*25.4) {
    drange = 10*25.4; 
    curmillis = lastmillis; 
  } else {
    drange = front_range;
    left_motor_volt = 0;
    right_motor_volt = 0;
  }
  range_pid.updateValues( drange, front_range, &left_desired_rpm);
  left_wheel_pid.updateValues( left_desired_rpm, left_actual_rpm, &left_motor_volt);
  right_wheel_pid.updateValues( left_desired_rpm, right_actual_rpm, &right_motor_volt);
}

// start function used to drive car and stop 12 inches before a wall and that 
// when wall is reached the car turn 180 degrees around
void start() {
  //Serial.print("here>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
  front_ping.updateRange( &front_range);
  while( front_range > RANGEF*25.4 && front_range != 0) {
    detachInterrupt(leftISR); 
    detachInterrupt(rightISR);
    curmillis = millis();
    attachInterrupt( leftISR, doLeftEncoder, CHANGE);
    attachInterrupt( rightISR, doRightEncoder, CHANGE);
    if(curmillis - lastmillis >= 50) {
      lastmillis = curmillis;
      front_ping.updateRange( &front_range);
      left_desired_rpm = 100;
      detachInterrupt(leftISR); 
      detachInterrupt(rightISR);
      getRPM(&left_actual_rpm, &left_clicks, encoder_resolution);
      getRPM(&right_actual_rpm, &right_clicks, encoder_resolution);
      attachInterrupt( leftISR, doLeftEncoder, CHANGE);
      attachInterrupt( rightISR, doRightEncoder, CHANGE);
      left_wheel_pid.updateValues( left_desired_rpm, left_actual_rpm, &left_motor_volt);
      right_wheel_pid.updateValues( left_desired_rpm, right_actual_rpm, &right_motor_volt);
      left_motor->run(FORWARD);
      right_motor->run(FORWARD);
      left_motor->setSpeed(left_motor_volt);
      right_motor->setSpeed(right_motor_volt);
      //debug();
    }
  }
  front_ping.updateRange( &front_range);
  if(front_range <= RANGEF*25.4) {
    //Serial.print("here>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    left_motor->run(RELEASE);
    right_motor->run(RELEASE);
    left_motor->setSpeed(0);
    right_motor->setSpeed(0);
    delay(1000);
    start_bool = true;
    zero_angle_turn(180);
    delay(1000);
  }
}
      
