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
  et = curmillis-lastmillis;
  et = et/1000/60;
  *RPM = (clks/encoderResolution/et);
  clks = 0;
  attachInterrupt(0, doEncoder, CHANGE);
}
