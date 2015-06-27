// counting with encoder
void doEncoder() {
  (digitalRead(m1.encoder_pin_a) == 
  digitalRead(m1.encoder_pin_b) ? m1.clks--:m1.clks++);
}
// calculate rpms
void getRPM( double *RPM, int clks, int encoderResolution) {
  // revolutions encoderResolution/clks
  detachInterrupt( 3);
  lastmillis = curmillis;
  curmillis = millis();
  et = curmillis-lastmillis;
  et = et/1000/60;
  *RPM = (clks/encoderResolution/et);
  clks = 0;
  attachInterrupt( 3, doEncoder, CHANGE);
}
