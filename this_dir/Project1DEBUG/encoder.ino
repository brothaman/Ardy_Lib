// counting with encoder
void doEncoder() {
  (digitalRead(pina) == digitalRead(pinb) ? clks--:clks++);
}
// calculate rpms
void getRPM( double *RPM) {
  // revolutions encoderResolution/clks
  detachInterrupt( 0);
  lastmillis = curmillis;
  curmillis = millis();
  *RPM = (clks/encoderResolution/(curmillis-lastmillis)*60*1000);
  Serial.print(curmillis-lastmillis);
  clks = 0;
  attachInterrupt(0, doEncoder, CHANGE);
}
