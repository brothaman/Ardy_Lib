#include <PID.h>



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
double kp = .15, ki = .1, kd =.01;
PID pid( &kp, &ki, &kd, 40, 0, 350, -350);
double dval = 12, aval=10, val=0;
void loop() {
  // put your main code here, to run repeatedly:
  char buf[45];
  while(Serial.available() > 0) {
    Serial.readBytesUntil('\n', buf, 45);
    val = atof(buf);
    Serial.print("Input Value: ");
    Serial.println(val);
    while( aval >= dval*(1+.15) || aval <= dval*(1 - .15) ) {
      pid.updateValues(dval, aval, &val);
      Serial.print("desired value: "); Serial.print(dval);
      Serial.print("  actual value: "); Serial.print(aval);
      Serial.print("  adjustment value: "); Serial.println(val);
      aval = val;
      delay(100);
    }
      
  }
}

