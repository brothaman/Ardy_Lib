
// input variables
int potpin = 1, photre = 0;
int potval, phoval;

// output variables
int buzpin = 6;
int freq;

int lastmillis = millis();
void setup() {
  // put your setup code here, to run once:
  pinMode( potpin, INPUT);
  pinMode( photre, INPUT);
  pinMode( buzpin, OUTPUT);
  
  // initialize all values
  potval = 0; phoval = 0; freq = 0;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  phoval = analogRead(photre);
  potval = analogRead(potpin);
  freq = map((phoval+potval), 0, 2*1023, 500, 4000);
  
  tone(buzpin, freq);
  if(millis() >= 250+lastmillis) {
    Serial.print("Potentiometer value is: ");Serial.println(potval);
    Serial.print("Photoresistor value is: ");Serial.println(phoval);
    Serial.print( "Buzzer tonal value is: ");Serial.println(  freq);
    lastmillis = millis();
  }

}
