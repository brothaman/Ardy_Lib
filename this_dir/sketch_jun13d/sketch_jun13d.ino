int mvolt = 0, mpin = 3;
int potpin = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(mpin,  OUTPUT);
  pinMode(potpin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  mvolt = map( analogRead(potpin), 0, 1023, 0, 255);
  analogWrite( mpin, mvolt);
}
