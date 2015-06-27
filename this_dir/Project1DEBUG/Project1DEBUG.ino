int mpin = 9, pina = 2, pinb = 4;
unsigned long lastmillis = 0, curmillis = 0;
volatile int clks = 0;
double rpm;
double mvolt = 0;
double encoderResolution=256;

void setup() {
  pinMode(pina, INPUT);
  pinMode(pinb, INPUT);
  digitalWrite(pina, HIGH);
  digitalWrite(pinb, HIGH);
  pinMode(mpin, OUTPUT);
  attachInterrupt(0, doEncoder, CHANGE);
  Serial.begin(9600);
}

void loop() {
  char buf[4] = {0,0,0,0};
  while(Serial.available() != 0) {
    Serial.readBytesUntil('\n', buf, 4);
    mvolt = atoi(buf);
  }
  analogWrite(mpin, mvolt);
  Serial.println(clks);
  getRPM( &rpm);
  Serial.print("Voltage to Motor Pin: "); Serial.println(mvolt*5.0/255.0);
  Serial.print("motor RPM: "); Serial.println(rpm);
  
  
  delay(1000);
}
