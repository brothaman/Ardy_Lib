/*
#include <Pixy.h>
#include <PixyI2C.h>
#include <PixyUART.h>
#include <TPixy.h>
*/

#include <AFMotor.h>
#include <ping.h>
#include <PID.h>
#include <motor.h>


// set up with encoder pins A and B as 2 and 4 respectively
struct motor_encoder{
  int motor_pin;
  double mvolt;
  int encoder_pin_a;
  int encoder_pin_b;
  double pid[3], actual_rpm, desired_rpm;
  int encoder_resolution;
  volatile int clks;
};

// motor & encoder structs initialized
struct motor_encoder m1, m2;

// ping sensor range variable
double range;

// Encoder stuffs
unsigned long lastmillis = 0, curmillis = 0, tsig = 0;
double et;
volatile int clks = 0;
int sample = 0;

// adafruit PMDC motor library implementation 
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  // put your setup code here, to run once:
  // data structure for motor 1
  m1.encoder_pin_a = 20;
  m1.encoder_pin_b = 21;
  m1.pid[0] = .01495; m1.pid[1] = 1.9914; m1.pid[2] = 0;
  m1.actual_rpm = 0; m1.desired_rpm = 0;
  m1.clks = 0; m1.encoder_resolution = 128;
  m1.mvolt = 0;
  
  // data structure for motor 2
  m2.encoder_pin_a = 20;
  m2.encoder_pin_b = 21;
  m2.pid[0] = .01495; m2.pid[1] = 1.9914; m2.pid[2] = 0;
  m2.actual_rpm = 0; m2.desired_rpm = 0;
  m2.clks = 0; m2.encoder_resolution = 128;
  m2.mvolt = 0;
  
  // set up pins
  pinMode( 47, OUTPUT);
  pinMode( m1.encoder_pin_a, INPUT);
  pinMode( m1.encoder_pin_b, INPUT);
  digitalWrite( m1.encoder_pin_a, HIGH);
  digitalWrite( m1.encoder_pin_b, HIGH);
  
  // setup for motor
  motor1.setSpeed( 0);
  motor1.run( RELEASE);
  motor2.setSpeed( 0);
  motor2.run( RELEASE);
  
  // attach ISR for encoders
  attachInterrupt( 3, doEncoder, CHANGE);

  // set up serial port for reading and writing
  Serial.begin(115200);
}

// run all constructors
ping p1( 44, 0);
PID p( &m1.pid[0], &m1.pid[1], &m1.pid[2], 350, -350, 255, 0);
double prange = 0;


void loop() {
  // put your main code here, to run repeatedly:
  detachInterrupt( 3);
  digitalWrite( 47, HIGH);
  prange = range;
  p1.updateRange(&range);
  digitalWrite( 47, LOW);
  attachInterrupt( 3, doEncoder, CHANGE);
  
  // determine if car is too close to the wall & set desired speed
  if(range*100/2.54 > 13) {
    motor1.run( FORWARD);
    motor2.run( FORWARD);
    motor1.setSpeed( 100);
    motor2.setSpeed( 100);
    m1.desired_rpm = 50;
  }else if(range*100/2.54 < 11) {
    motor1.run( BACKWARD);
    motor2.run( BACKWARD);
    motor1.setSpeed( 100);
    motor2.setSpeed( 100);
    m1.desired_rpm = -50;
  }else {
    m1.desired_rpm = 0;
  }
  
  // detach isr connected to encoders
  detachInterrupt( 3);
  // update motor voltage here
  p.updateValues( abs(m1.desired_rpm), m1.actual_rpm, &m1.mvolt);
  sample++;
  attachInterrupt( 3, doEncoder, CHANGE);
  getRPM( &m1.actual_rpm, m1.clks, m1.encoder_resolution);
  // motor1.setSpeed( abs(m1.mvolt));
  // motor2.setSpeed( abs(m1.mvolt));
  debug();\
}
