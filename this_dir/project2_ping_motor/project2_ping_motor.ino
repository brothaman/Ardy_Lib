#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#include <ping.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Constructors
ping p( 44, 0);
Adafruit_DCMotor *motor = AFMS.getMotor(1);
double range;
int s;

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  pinMode( 45, OUTPUT);
  motor->setSpeed(0);
  motor->run( RELEASE);
  Serial.begin(9600);

}

void loop() {
  motor->run(FORWARD);
  // put your main code here, to run repeatedly:
  digitalWrite( 45, HIGH);
  p.updateRange( &range);
  Serial.print("Range in cm: ");Serial.println(range/.0254);
  digitalWrite( 45, LOW);
  
  if(range/.0254 > 12) {
    Serial.print("hello world");
    s = 200;
  } else{ 
    s = 0;
  }
  motor->setSpeed(s);
}

