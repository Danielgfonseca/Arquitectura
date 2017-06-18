/*
Name:		SensorUltrasonicoInterrupts.ino
Created:	01/06/2017 11:33:45
Author:	danie
*/
#include <DueTimer-master\DueTimer.h>
#include "DueTimer.h"

unsigned long segundo;
unsigned  long tempoeco;
long nleituras;
byte triger;
long nloop;
bool mostrar;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	pinMode(13, OUTPUT);
	pinMode(12, INPUT);
	segundo = 1000;
	nloop = 0;
	nleituras = 0;
	mostrar = false;
	triger = HIGH;
	//Timer1.initialize(25000); //Função para arduino uno
	//Timer1.attachInterrupt(triggerSensor)
	//Timer3.attachInterrupt(triggerSensor).start(25000); //Chamar a função 'triggerSensor' a cada 25000 microsegundos ( 25ms )
	Timer3.attachInterrupt(triggerSensor).setFrequency(20).start(); //Chamar a função 'triggerSensor' 20 vezes por segundo
	attachInterrupt(0, eco, CHANGE);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (mostrar) {
		Serial.print("Tempo Eco: ");
		Serial.println(tempoeco);
		mostrar = false;
	}

	nloop++;

	if (millis() >= segundo) {
		Serial.print("Ciclos: ");
		Serial.println(nloop);
		Serial.print("Leituras: ");
		Serial.println(nleituras);
		segundo += 1000;
		nloop = 0;
		nleituras = 0;
	}
}


void triggerSensor() {
	digitalWrite(13, triger);
	triger = !triger;
}


void eco() {
	if (digitalRead(12)) {
		tempoeco = micros();
	}
	else {
		tempoeco = ((micros() - tempoeco));
		mostrar = true;
		nleituras++;
	}
}