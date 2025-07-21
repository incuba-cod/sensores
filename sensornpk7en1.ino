#include <SoftwareSerial.h>

#define RE 4
SoftwareSerial mod(32, 13);  // RX, TX

float humedad, temperatura, ph;
int conductividad, nitrogeno, phosforo, potasio;

void setup() {
  Serial.begin(115200);
  mod.begin(4800);
  pinMode(RE, OUTPUT);
  digitalWrite(RE, LOW);
  delay(2000);
}

void loop() {
  const byte soilSensorRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08};
  byte soilSensorResponse[19];

  digitalWrite(RE, HIGH);
  delay(10);
  mod.write(soilSensorRequest, sizeof(soilSensorRequest));
  digitalWrite(RE, LOW);
  delay(10);

  unsigned long startTime = millis();
  while (mod.available() < 19 && millis() - startTime < 1000) {
    delay(1);
  }

  if (mod.available() >= 19) {
    for (int i = 0; i < 19; i++) {
      soilSensorResponse[i] = mod.read();
    }

    humedad = int(soilSensorResponse[3] << 8 | soilSensorResponse[4]) / 10.0;
    temperatura = int(soilSensorResponse[5] << 8 | soilSensorResponse[6]) / 10.0;
    conductividad = int(soilSensorResponse[7] << 8 | soilSensorResponse[8]);
    ph = int(soilSensorResponse[9] << 8 | soilSensorResponse[10]) / 10.0;
    nitrogeno = int(soilSensorResponse[11] << 8 | soilSensorResponse[12]);
    phosforo = int(soilSensorResponse[13] << 8 | soilSensorResponse[14]);
    potasio = int(soilSensorResponse[15] << 8 | soilSensorResponse[16]);

    Serial.println("Datos del sensor de suelo:");
    Serial.println("Humedad: " + String(humedad));
    Serial.println("Temperatura: " + String(temperatura));
    Serial.println("Conductividad: " + String(conductividad));
    Serial.println("pH: " + String(ph));
    Serial.println("Nitrógeno: " + String(nitrogeno));
    Serial.println("Fósforo: " + String(phosforo));
    Serial.println("Potasio: " + String(potasio));
  } else {
    Serial.println("Sensor timeout o datos incompletos");
  }

  delay(5000);  // Espera entre lecturas
}
