#include <AFMotor.h>

AF_DCMotor motor3(1);
AF_DCMotor motor4(2);


void setup() {
  // put your setup code here, to run once:
  motor3.setSpeed(0);
  motor3.run(RELEASE);
  motor4.setSpeed(0);
  motor4.run(RELEASE);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

}
