#include "DHT.h"

const int LEDR = 10;
const int LEDG = 11;
const int LEDB = 12;
const int BUZZER = 6;
const int PINO_DHT = 2;

float temperatura;
float umidade;

const float TEMP_CRITICA_MAX = 35.0;
const float TEMP_CRITICA_MIN = 15.0;
const float UMID_CRITICA = 20;
const float TEMP_ALERTA_MAX = 30.0;
const float TEMP_ALERTA_MIN = 20.0;
const float UMID_ALERTA = 30.0;

DHT dht(PINO_DHT, DHT11);

void setup() {
  dht.begin();

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void ativarLED(int statusR, int statusG, int statusB) {
  digitalWrite(LEDR, statusR);
  digitalWrite(LEDG, statusG);
  digitalWrite(LEDB, statusB);
}

void ativarAlerta() {

  for (int i = 0; i < 4; i++) {
    ativarLED(HIGH, LOW, LOW);
    tone(BUZZER, 1000);
    delay(500);
    digitalWrite(LEDR, LOW);
    noTone(BUZZER);
    delay(1000);
  }
}

void loop() {
  delay(2000);

  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    ativarLED(HIGH, HIGH, HIGH);
    noTone(BUZZER);

  } else {

    if (temperatura > TEMP_CRITICA_MAX || temperatura < TEMP_CRITICA_MIN || umidade < UMID_CRITICA) {
      ativarAlerta();
    } else if (temperatura > TEMP_ALERTA_MAX || temperatura < TEMP_ALERTA_MIN || umidade < UMID_ALERTA) {
      ativarLED(LOW, HIGH, LOW);
    } else {
      ativarLED(LOW, LOW, HIGH);
    }
  }

}
