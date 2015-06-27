// debug function
void debug() {
  Serial.print("range: "); Serial.println(range*100/2.54);
  Serial.print("desired value: "); Serial.println(m1.desired_rpm);
  Serial.print("actual value: "); Serial.println(m1.actual_rpm);
  Serial.print("adjustment value: "); Serial.println(m1.mvolt);
  Serial.print("number of clicks from motor 1: "); Serial.println(m1.clks);
}
