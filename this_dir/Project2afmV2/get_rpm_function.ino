// calculate rpms
void getRPM( double *RPM, volatile int *clks, int encoderResolution) {
  // revolutions encoderResolution/clks
  detachInterrupt( leftISR);
  detachInterrupt( rightISR);
  *RPM = (*clks/et/encoderResolution);
  *clks = 0;
  attachInterrupt( leftISR, doLeftEncoder, CHANGE);
  attachInterrupt( rightISR, doRightEncoder, CHANGE);
}
