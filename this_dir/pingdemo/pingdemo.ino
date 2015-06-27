#include <maxsonar.h>

maxsonar p( 8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

double range = 0;

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite( 2, HIGH);
  delay(1);
  p.updateRange(&range);
  // digitalWrite( 2, LOW);
  Serial.println(range,6);
}
