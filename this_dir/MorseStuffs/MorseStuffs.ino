#include <Morsetuff.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

Morse morse(9);
int space;
bool trip = false;
int cnt = 0;

void loop() {
  // put your main code here, to run repeatedly:
  char buf[1024];
  for (int i = 0; i < 1024; i++) {
    buf[i] = '\0';
  }
  space = 0;
  while (Serial.available() > 0) {
    trip = true;
    buf[space] = toupper(Serial.read());
    space++;
  }
  if (trip) {
    cnt++;
    morse.sendMessage(buf);
    trip = false;
  }
}
/*

*/
