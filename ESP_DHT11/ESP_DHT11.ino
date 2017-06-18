/* Daniel Fonseca - 18 de Junho
*
* Este programa envia os dados coletados do DHT11 para a plataforma de IoT
* thingspeak.com
*/

#include <WiFi.h>
#include <DHT_U.h>
#include "DHT.h"

#define DHT_DATA_PIN 2
#define DHTTYPE DHT11

const char* ssid = "MEO-1A7FE9";
//Definir a senha da rede WiFi
const char* password = "14DA5A302D";

//Colocar a API Key para escrita neste campo
//Ela é fornecida no canal que foi criado na aba API Keys
String apiKey = "O7KSUR1MG5Q337DC";
const char* server = "api.thingspeak.com";

DHT dht(DHT_DATA_PIN, DHTTYPE);
WiFiClient client;

void setup() {
	//Configuração da UART
	Serial.begin(9600);
	//Inicia o WiFi
	WiFi.begin(ssid, password);

	//Espera a conexão no router
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	dht.begin();

	//Logs na porta serial
	Serial.println("");
	Serial.print("Conectado na rede ");
	Serial.println(ssid);
	Serial.print("IP: ");
	Serial.println(WiFi.localIP());
}

void loop() {

	//Espera 20 segundos para fazer a leitura
	delay(20000);
	//Leitura de umidade
	float umidade = dht.readHumidity();
	//Leitura de temperatura
	float temperatura = dht.readTemperature();

	//Se não for um numero retorna erro de leitura
	if (isnan(umidade) || isnan(temperatura)) {
		Serial.println("Erro ao ler o sensor!");
		return;
	}

	//Inicia um client TCP para o envio dos dados
	if (client.connect(server, 80)) {
		String postStr = apiKey;
		postStr += "&amp;field1=";
		postStr += String(temperatura);
		postStr += "&amp;field2=";
		postStr += String(umidade);
		postStr += "\r\n\r\n";

		client.print("POST /update HTTP/1.1\n");
		client.print("Host: api.thingspeak.com\n");
		client.print("Connection: close\n");
		client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
		client.print("Content-Type: application/x-www-form-urlencoded\n");
		client.print("Content-Length: ");
		client.print(postStr.length());
		client.print("\n\n");
		client.print(postStr);

		//Logs na porta serial
		Serial.print("Temperatura: ");
		Serial.print(temperatura);
		Serial.print(" Umidade: ");
		Serial.println(umidade);
	}
	client.stop();
}