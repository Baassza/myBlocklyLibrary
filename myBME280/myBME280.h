#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;


float BME280Read(int value) {
  float res = 0;
  bme.begin(0x76);
  switch (value) {
    case 1:
      res = bme.readTemperature();
      break;
    case 2:
      res = bme.readPressure() / 100.0F;
      break;
    case 3:
      res = bme.readAltitude(SEALEVELPRESSURE_HPA);
      break;
    case 4:
      res = bme.readHumidity();
      break;
    default :
     return;
  }
  return res;

}
