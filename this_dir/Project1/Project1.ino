#include <PID.h>
#include <motor.h>

// set up with encoder pins A and B as 2 and 4 respectively
int pina = 2, pinb = 4;
int mpin = 9; double mvolt = 15;
double kp = .01495, ki = 1.9914, kd = 0.0000000, arpm = 0, drpm = 0;

// Encoder stuffs
double encoderResolution = 512;
unsigned long lastmillis = 0, curmillis = 0, tsig = 0;
double et;
volatile int clks = 0;
int sample = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pina, INPUT);
  pinMode(pinb, INPUT);
  digitalWrite( pina, HIGH);
  digitalWrite( pinb, HIGH);
  
  pinMode(mpin, OUTPUT);
  attachInterrupt( 0, doEncoder, CHANGE);
  Serial.begin(115200);
}

// run all constructors
motor m( 9);
PID p( &kp, &ki, &kd, 800, 0, 255, 15);


void loop() {
  // put your main code here, to run repeatedly:
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
  attachInterrupt(0, doEncoder, CHANGE);
  analogWrite(mpin, mvolt);
  //Serial.print("desired value: "); Serial.print(drpm);
  //Serial.print(",  actual value: ");
  Serial.print(sample); Serial.print(",");
  Serial.print(drpm); Serial.print(",");
  Serial.print(arpm); Serial.print("\n");
  //Serial.print(",  adjustment value: "); Serial.println(mvolt);
  getRPM( &arpm);
  delay(50);
}


