long pont;
long nloop;
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
	valor = 6;
	nloop = 0;
	tempo = 0;
	segundo = 1000;
	estadobotao = 0;
	Serial.begin(115200);
}

void loop()
{
	pont = analogRead(A0);
	pont = pont * 2950 / 1023 + 50;

	if (digitalRead(2) != estadobotao)
	{
		estadobotao = !estadobotao;
		pont = 0;
	}

	tempoatual = millis();
	if (tempoatual - tempo >= pont)
	{
		tempo = tempoatual;
		digitalWrite(valor, LOW);
		if (estadobotao)
		{
			valor == 6 ? valor = 13 : valor--;
		}
		else
		{
			valor == 13 ? valor = 6 : valor++;
		}
		digitalWrite(valor, HIGH);
	}

	nloop++;

	if (tempoatual >= segundo)
	{
		Serial.println(nloop);
		segundo += 1000;
		nloop = 0;
	}
}