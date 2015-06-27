int button = 0, state = 0;
int led = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(button) == HIGH) {
    state = 1-state;
    delay(50);
  }
  (state==1 ? digitalWrite(button, HIGH):digitalWrite(button, LOW));
}
