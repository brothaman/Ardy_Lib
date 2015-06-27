void setup() {
  Serial.begin(9600);
  int mygrades[] = {98, 89,94,85,76, 94, 68, 97, 87, 88, 91, 94};
  double average = 0;
  //Serial.println("%lu \n", sizeof(mygrades)/sizeof(int));
				
  // add all grades
  for(int i = 0; i <= sizeof(mygrades)/sizeof(int)-1; i++) {
    average = average + mygrades[i];
  }
  average = average/(sizeof(mygrades)/sizeof(int));
  Serial.println( average, 2);
}
void loop() {}

