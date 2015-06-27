int accelxvalue = 0, accelyvalue = 0, accelzvalue = 0;
float vector[3] = {0.0, 0.0, 0.0};
struct A {
  float xReading;
  float yReading;
  float zReading;
}acceldevice;

float GETaccelxvalue(){
  return acceldevice.xReading;
}

float GETaccelyvalue() {
  return acceldevice.yReading;
}

float GETaccelzvalue() {
  return acceldevice.zReading;
}

void setup() {
  Serial.begin(115200);
}
void loop() {
  accelxvalue = GETaccelxvalue();
  accelyvalue = GETaccelyvalue();
  accelzvalue = GETaccelzvalue();
  int magnitude = sqrt(pow( accelxvalue, 2) + pow( accelyvalue, 2) + pow( accelzvalue, 2));
  
  vector[0] = GETaccelxvalue()/magnitude;
  vector[1] = GETaccelyvalue()/magnitude;
  vector[2] = GETaccelzvalue()/magnitude;
  
  for(int i = 0; i < sizeof(vector)/sizeof(float); i++) {
    Serial.println(vector[i]);
  }
}
