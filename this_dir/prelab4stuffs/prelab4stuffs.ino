float A, B;
int w = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buf[10] = {0,0,0,0,0,0,0,0,0,0};
  while(Serial.available()) {
    Serial.readBytesUntil( '\n', buf, 10);
    if(w%2) {
      A = atof( buf);
    }else {
      B = atof( buf);
      evaluate( A, B);
    }
    w++;
  }
}
void evaluate( float a, float b) {
  Serial.print("Addition: ");Serial.println(a+b);
  Serial.print("Subtraction: ");Serial.println(a-b);
  Serial.print("Multiplication: ");Serial.println(a*b);
  Serial.print("Division: ");Serial.println(a/b);
  Serial.print("Logical Greater-Than: ");Serial.println(a>b);
  Serial.print("Logical Less-than-Equal: ");Serial.println(a<=b);
  Serial.print("Logical Not-Equal: ");Serial.println(a!=b);
  Serial.print("Logical Equal: ");Serial.println(a=b);
}
