int pna = 3;
int pnb = 5;
int clks = 0;

void setup() {
  pinMode(pna, INPUT);
  pinMode(pnb, INPUT);
  
  digitalWrite(pna, HIGH);
  digitalWrite(pnb, HIGH);
  
  attachInterrupt(1, doEncoder, CHANGE);
  Serial.begin(115200);
}

void loop() {}

void doEncoder() {
  
 // implement 2 possibilities for ease of computation
  if(digitalRead(pna) == digitalRead(pnb)){
    // CCW
    clks--;
  } else{
    // CW
    clks++;
  }
  Serial.println(clks);

}
