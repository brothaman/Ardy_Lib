#include <Arduino.h>
#include <Morsetuff.h>



Morse::Morse(int p) {
	Morse::initiateLib();
	Morse::pin = p;
	pinMode(Morse::pin, OUTPUT);
	Serial.println("Initializing Morse Code Library");
}

void Morse::initiateLib() {
	cycon[0].letter = 'A'; cycon[0].morse = ".-";
	cycon[1].letter = 'B'; cycon[1].morse = "-...";
	cycon[2].letter = 'C'; cycon[2].morse = "-.-.";
	cycon[3].letter = 'D'; cycon[3].morse = "-..";
	cycon[4].letter = 'E'; cycon[4].morse = ".";
	cycon[5].letter = 'F'; cycon[5].morse = "..-.";
	cycon[6].letter = 'G'; cycon[6].morse = "--.";
	cycon[7].letter = 'H'; cycon[7].morse = "....";
	cycon[8].letter = 'I'; cycon[8].morse = "..";
	cycon[9].letter = 'J'; cycon[9].morse = ".---";
	cycon[10].letter = 'K'; cycon[10].morse = "-.-";
	cycon[11].letter = 'L'; cycon[11].morse = ".-..";
	cycon[12].letter = 'M'; cycon[12].morse = "--";
	cycon[13].letter = 'N'; cycon[13].morse = "-.";
	cycon[14].letter = 'O'; cycon[14].morse = "---";
	cycon[15].letter = 'P'; cycon[15].morse = ".--.";
	cycon[16].letter = 'Q'; cycon[16].morse = "--.-";
	cycon[17].letter = 'R'; cycon[17].morse = ".-.";
	cycon[18].letter = 'S'; cycon[18].morse = "...";
	cycon[19].letter = 'T'; cycon[19].morse = "-";
	cycon[20].letter = 'U'; cycon[20].morse = "..-";
	cycon[21].letter = 'V'; cycon[21].morse = "...-";
	cycon[22].letter = 'W'; cycon[22].morse = ".--";
	cycon[23].letter = 'X'; cycon[23].morse = "-..-";
	cycon[24].letter = 'Y'; cycon[24].morse = "-.--";
	cycon[25].letter = 'Z'; cycon[25].morse = "--..";
	cycon[26].letter = '1'; cycon[26].morse = ".---";
	cycon[27].letter = '2'; cycon[27].morse = "..---";
	cycon[28].letter = '3'; cycon[28].morse = "...--";
	cycon[29].letter = '4'; cycon[29].morse = "....-";
	cycon[30].letter = '5'; cycon[30].morse = ".....";
	cycon[31].letter = '6'; cycon[31].morse = "-....";
	cycon[32].letter = '7'; cycon[32].morse = "--...";
	cycon[33].letter = '8'; cycon[33].morse = "---..";
	cycon[34].letter = '9'; cycon[34].morse = "----.";
	cycon[35].letter = '0'; cycon[35].morse = "-----";
	cycon[36].letter = '/'; cycon[36].morse = "-..-.";
	cycon[37].letter = '*'; cycon[37].morse = ".-.-.";
	cycon[38].letter = '.'; cycon[38].morse = ".-.-.-";
	cycon[39].letter = '_'; cycon[39].morse = "-....-";
	cycon[40].letter = ','; cycon[40].morse = "--..--";
	cycon[41].letter = '?'; cycon[41].morse = "..--..";
	cycon[42].letter = ' '; cycon[42].morse = " ";
}

void Morse::sendMessage( char * arg) {
	char * morse;
	for(int i = 0; i < strlen(arg); i ++) {
		morse = eval(arg[i]);
		for(int j = 0; j < strlen(morse); j++){
			if(morse[j] == '.') {
				dot();
			} else if( morse[j] == '-') {
				dash();
			} else if( morse[j] == ' ') {
				space();
			}
		}
	}
	Serial.print('\n');
	Serial.print(arg);
}

char * Morse::eval(char c) {
	int i = 0;
	while(c!=cycon[i].letter) {
		i++;
	}
	return cycon[i].morse;
}
void Morse::dot() {
	Serial.print(".");
	digitalWrite( Morse::pin, HIGH);
	delay(125);
	digitalWrite( Morse::pin, LOW);
	delay(375);
}
void Morse::dash() {
	Serial.print("-");
	digitalWrite( Morse::pin, HIGH);
	delay(375);
	digitalWrite( Morse::pin, LOW);
	delay(125);
}
void Morse::space() {
	Serial.print("\n");
	digitalWrite(Morse::pin, LOW);
	delay(500);
}
