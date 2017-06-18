/*
Name:		SonarInterrupts.ino
Created:	08/06/2017 13:00:46
Author:	danie
*/

// the setup function runs once when you press reset or power the board
#include <TimerOne.h>

unsigned long segundo;
unsigned  long tempoeco;
long numerodeleituras;
byte triger;
long cloop;
bool mostrar;

void setup() {

	pinMode(4, OUTPUT);
	pinMode(2, INPUT);
	Serial.begin(115200);
	Timer1.initialize(25000);
	Timer1.attachInterrupt(trigere);
	attachInterrupt(0, eco, CHANGE);
	segundo = 1000;
	triger = HIGH;
	cloop = 0;
	mostrar = false;
	numerodeleituras = 0;

}

void loop() {

	if (mostrar) {
		Serial.print("Tempoeco: ");
		Serial.println(tempoeco);
		mostrar = false;
	}

	cloop++;

	if (millis() >= segundo) {
		Serial.print("Ciclos: ");
		Serial.println(cloop);
		Serial.print("Leituras: ");
		Serial.println(numerodeleituras);
		segundo += 1000;
		cloop = 0;
		numerodeleituras = 0;
	}

}


void trigere() {
	digitalWrite(4, triger);
	triger = !triger;
}



void eco() {
	if (digitalRead(2)) {
		tempoeco = micros();
	}
	else {
		tempoeco = ((micros() - tempoeco));
		mostrar = true;
		numerodeleituras++;
	}
}



