#include <SPI.h>
#include <SD.h>

#define SD_CS 5  // Pin CS para la tarjeta SD (ajusta según tu placa)
File myFile;

void setup() {
  Serial.begin(115200);

  // Inicializar la tarjeta SD
  if (!SD.begin(SD_CS)) {
    Serial.println("Fallo al montar la tarjeta SD");
    while (1);  // Detener ejecución
  }

  Serial.println("Tarjeta SD inicializada correctamente");

  // Crear archivo con encabezado si no existe
  if (!SD.exists("/datos.csv")) {
    myFile = SD.open("/datos.csv", FILE_WRITE);
    if (myFile) {
      myFile.println("Fecha,Humedad,Temperatura,pH,Batería");
      myFile.close();
      Serial.println("Archivo creado con encabezado");
    }
  }
}

void loop() {
  // Simulación de datos
  String fecha = "2025-07-21 10:30:00";
  float humedad = 45.3;
  float temperatura = 26.1;
  float ph = 6.7;
  float bateria = 3.8;

  // Abrir archivo y escribir
  myFile = SD.open("/datos.csv", FILE_APPEND);
  if (myFile) {
    myFile.print(fecha); myFile.print(",");
    myFile.print(humedad); myFile.print(",");
    myFile.print(temperatura); myFile.print(",");
    myFile.print(ph); myFile.print(",");
    myFile.println(bateria);
    myFile.close();
    Serial.println("Datos guardados en SD");
  } else {
    Serial.println("Error al abrir datos.csv");
  }

  delay(10000);  // Espera 10 segundos antes de guardar otra vez
}
