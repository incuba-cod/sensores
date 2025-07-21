#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;
float factorEscala = 0.125F;  // mV por bit
float bateria;

void setup() {
  Serial.begin(115200);
  if (!ads.begin()) {
    Serial.println("Fallo al inicializar ADS1115");
    while (1);
  }
  delay(1000);
}

float bateria_obtener() {
  byte a = 0;
  float bat = 0;
  do {
    short adc0 = ads.readADC_SingleEnded(0);
    bat += (adc0 * factorEscala) / 1000.0;
    a++;
  } while (a <= 100);

  bat = bat / 101;
  bat = bat * 4.2 / 1.485;  // Ajustar según divisor resistivo
  return bat;
}

void loop() {
  bateria = bateria_obtener();
  Serial.print("Voltaje batería: ");
  Serial.print(bateria, 3);
  Serial.println(" V");

  delay(5000);  // Espera entre lecturas
}
