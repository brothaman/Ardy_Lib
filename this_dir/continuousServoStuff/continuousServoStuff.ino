/*
Calibrate Continuous Rotation Servo
 
// based on <http://arduino.cc/en/Tutorial/Sweep>
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.
 
modified Jan 2013
by Markus Loder-Taucher
*/
 
// include the TinkerKit library
#include <TinkerKit.h>
  
// include the Servo library
#include <Servo.h> 
   
Servo TKContinuousRotationServo;  // create servo object to control a servo 
                                  // a maximum of eight servo objects can be created 
   
int pos = 0;    // variable to store the servo position
 
                // adjust potentiometer taht the servo is not moving or making any noise
   
void setup() 
{ 
  TKContinuousRotationServo.attach(O0);  // attaches the servo on pin 9 to the servo object 
} 
   
   
void loop() 
{ 
    pos = 90;
    TKContinuousRotationServo.write(pos);
    delay(1000);
    pos = 0;
    TKContinuousRotationServo.write(pos);
    delay(1000);
}
