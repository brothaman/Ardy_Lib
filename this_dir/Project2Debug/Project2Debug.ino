#include <AFMotor.h>
#include <PID.h>
#include <motor.h>

// set up with encoder pins A and B as 2 and 4 respectively
int pina = 20, pinb = 21;
double mvolt = 15;
double kp = .01495, ki = 1.9914, kd = 0, arpm = 0, drpm = 0;

// Encoder stuffs
double encoderResolution = 128;
unsigned long lastmillis = 0, curmillis = 0, tsig = 0;
double et;
volatile int clks = 0;
int sample = 0;

AF_DCMotor motor(1);

void setup() {
  // put your setup code here, to run once:
  pinMode(pina, INPUT);
  pinMode(pinb, INPUT);
  digitalWrite( pina, HIGH);
  digitalWrite( pinb, HIGH);
  
  // motor setup
  motor.setSpeed(0);
  motor.run(RELEASE);
  
  attachInterrupt( 3, doEncoder, CHANGE);
  Serial.begin(115200);
}

// run all constructors
PID p( &kp, &ki, &kd, 300, 0, 255, 15);


void loop() {
  // put your main code here, to run repeatedly:
  motor.run(FORWARD);
  char buf[4];
  while (Serial.available() != 0) {
    Serial.readBytesUntil('\n', buf, 45);
    drpm = atof(buf);
    //Serial.print(drpm);
  }
  //Serial.print("Input Value: ");Serial.println(drpm);
  detachInterrupt(0);
  /*
  if(millis() >= tsig+10000) {
    tsig = tsig + 10000;
    drpm = 200-drpm;
  }
  */
  p.updateValues(drpm, arpm, &mvolt);
  sample++;
  attachInterrupt(3, doEncoder, CHANGE);
  motor.setSpeed( mvolt);
  //Serial.print("desired value: "); Serial.print(drpm);
  //Serial.print(",  actual value: ");
  Serial.print(sample); Serial.print(",");
  Serial.print(drpm); Serial.print(",");
  Serial.print(arpm); Serial.print(", ");
  Serial.println(clks);
  getRPM( &arpm);
  delay(50);
}

// counting with encoder
void doEncoder() {
  (digitalRead(pina) == digitalRead(pinb) ? clks--:clks++);
}
// calculate rpms
void getRPM( double *RPM) {
  // revolutions encoderResolution/clks
  detachInterrupt( 0);
  lastmillis = curmillis;
  curmillis = millis();
  et = curmillis-lastmillis;
  et = et/1000/60;
  *RPM = (clks/encoderResolution/et);
  clks = 0;
  attachInterrupt(3, doEncoder, CHANGE);
}


