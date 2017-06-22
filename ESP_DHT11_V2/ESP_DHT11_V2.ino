/*
 Name:		ESP_DHT11_V2.ino
 Created:	22/06/2017 00:16:48
 Author:	danie
*/

#include <DHT_U.h>
#include <DHT.h>
#include <WiFiUdp.h>
#include <WiFiType.h>
#include <WiFiSTA.h>
#include <WiFiServer.h>
#include <WiFiScan.h>
#include <WiFiMulti.h>
#include <WiFiGeneric.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WiFi.h>


#define DHT_DATA_PIN 2
#define DHTTYPE DHT11

//Dados para ligar a rede
const char* ssid = "MEO-1A7FE9";
const char* password = "14DA5A302D";

//API Key e ID do Thingspeak
unsigned long myChannelNumber = 289381;
String apiKey = "O7KSUR1MG5Q337DC";
const char* server = "api.thingspeak.com";

DHT dht(DHT_DATA_PIN, DHTTYPE);
WiFiClient client;
float temperature, humidity;
float prevTemp = 0;
int sent = 0;

void setup() {
	Serial.begin(115200);
	connectWifi();
}

void loop() {
	static boolean data_state = false;
	temperature = dht.readTemperature();
	humidity = dht.readHumidity();
	Serial.print("Temperature Value is :");
	Serial.print(temperature);
	Serial.println("C");
	Serial.print("Humidity Value is :");
	Serial.print(humidity);
	Serial.println("%");

	if (temperature != prevTemp)
	{
	sendTeperatureTS(temperature);
	prevTemp = temperature;
	}

	delay(30000); // Actualizar de 30s em 30s
}

void connectWifi()
{
	Serial.print("Connecting to " + *ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("Connected");
	Serial.println("");
}

void sendTeperatureTS(float temperature)
{
	WiFiClient client;

	if (client.connect(server, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
		Serial.println("WiFi Client connected ");

		String postStr = apiKey;
		postStr += "&field1=";
		postStr += String(temperature);
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
		delay(1000);

	}
	sent++;
	client.stop();
}
