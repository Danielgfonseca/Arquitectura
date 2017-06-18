/*
Name:		SensorUltrasonico.ino
Created:	25/05/2017 14:53:27
Author:	danie
*/

unsigned long tempoactualmillis;
unsigned long tempomillis;
unsigned long segundo;
unsigned  long tempoeco;
long nleituras;
byte triger;
long nloop;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(13, OUTPUT);
	pinMode(12, INPUT);
	Serial.begin(115200);
	tempomillis = 0;
	segundo = 1000;
	triger = HIGH;
	nloop = 0;
	nleituras = 0;
}

// the loop function runs over and over again until power down or reset
void loop() {
	tempoactualmillis = millis();
	if (tempoactualmillis >= tempomillis) {
		tempomillis += 25;
		triger = !triger;
		digitalWrite(13, triger);
		if (triger) {
			tempoeco = pulseIn(12, LOW);
			nleituras++;
			Serial.print("Tempo Eco: ");
			Serial.println(tempoeco);
		}
	}

	nloop++;

	//tempoactualmillis = millis();     
	if (tempoactualmillis >= segundo) {
		Serial.println("Por segundo");
		Serial.print("Ciclos: ");
		Serial.println(nloop);
		Serial.print("Leituras: ");
		Serial.println(nleituras);
		segundo += 1000;
		nloop = 0;
		nleituras = 0;
	}
}
