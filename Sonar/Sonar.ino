/*
Name:		Sonar.ino
Created:	07/06/2017 11:51:29
Author:	danie
*/


unsigned long tempoactualmillis;
unsigned long tempomillis;
unsigned long segundo;
unsigned  long tempoeco;
long numerodeleituras;
byte triger;
long cloop;

void setup() {

	pinMode(4, OUTPUT);
	pinMode(2, INPUT);
	Serial.begin(115200);
	tempomillis = 0;
	segundo = 1000;
	triger = HIGH;
	cloop = 0;
	numerodeleituras = 0;

}

void loop() {

	tempoactualmillis = millis();
	if (tempoactualmillis >= tempomillis) {
		tempomillis += 25;
		digitalWrite(4, triger);
		triger = !triger;
		if (triger) {
			tempoeco = pulseIn(2, HIGH);
			numerodeleituras++;
			Serial.print("Tempoeco: ");
			Serial.println(tempoeco);
		}
	}

	cloop++;
	tempoactualmillis = millis();
	if (tempoactualmillis >= segundo) {
		Serial.print("Ciclos: ");
		Serial.println(cloop);
		Serial.print("Leituras: ");
		Serial.println(numerodeleituras);
		segundo += 1000;
		cloop = 0;
		numerodeleituras = 0;
	}

}
