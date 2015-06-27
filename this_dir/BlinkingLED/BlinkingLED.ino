int yellowPin = 13;

void setup() {
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}

int blinks = 0; // number of blinks

void loop() {
  while( blinks < 15){
/*    digitalWrite(13,HIGH);
    delay(100);// wait for 1e3 milliseconds
    digitalWrite(13,LOW);
    delay(50);// wait for .5e3 milliseconds*/
    digitalWrite(12,HIGH);
    delay(1000);
    digitalWrite(12,LOW);
    delay(500);
    blinks++;
  }
}
