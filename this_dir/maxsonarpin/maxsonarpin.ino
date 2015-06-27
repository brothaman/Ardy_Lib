#include <maxsonar.h>

maxsonar m( 11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

double range;

void loop() {
  // put your main code here, to run repeatedly:
  m.updateRange( &range);
  Serial.print("range in m: "); Serial.println(range);
}
