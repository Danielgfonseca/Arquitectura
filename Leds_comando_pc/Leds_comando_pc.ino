long pont;
long cloop;
unsigned long tempo;
unsigned long segundo;
unsigned long tempoatual;
unsigned char valor;
bool estadobotao;

void setup()
{
	for (int i = 6; i < 14; i++)
	{
		pinMode(i, OUTPUT);
	}
	pinMode(2, INPUT);

	pinMode(3, OUTPUT);

	valor = 6;
	cloop = 0;
	tempo = 0;
	segundo = 1000;
	estadobotao = 0;

	Serial.begin(115200);
	Serial.println("Controlar Leds por comandos");
	Serial.println("'D'-Direta 'E'-Esquerda '1,2,3,4,5,6,7,8'-Ligar Leds");
	Serial.print('\n');
}

char rx_byte = 0;

void loop()
{
	pont = analogRead(A0);
	pont = pont * 2950 / 1023 + 50;

	if (digitalRead(2) != estadobotao)
	{
		estadobotao = !estadobotao;
		pont = 0;
	}

	if (Serial.available() > 0)
	{
		rx_byte = Serial.read();

		if (rx_byte == '3')
		{
			Serial.print("Numero carregado: ");
			Serial.println(rx_byte);
			digitalWrite(3, HIGH);
		}
		else
		{
			Serial.print("Desligado Led");
			digitalWrite(3, LOW);
		}
	}

	tempoatual = millis();
	if (tempoatual - tempo >= pont)
	{
		tempo = tempoatual;
		digitalWrite(valor, LOW);
		if (rx_byte == '1')
		{
			valor == 6 ? valor = 13 : valor--;
		}
		else if (rx_byte == '2')
		{
			valor == 13 ? valor = 6 : valor++;
		}
		digitalWrite(valor, HIGH);
	}

	cloop++;

	if (tempoatual >= segundo)
	{
		Serial.println(cloop);
		segundo += 1000;
		cloop = 0;
	}
}