#include <OneWire.h>
#include <DallasTemperature.h>

float DS18B20_Read(int port, bool unit = false) {
  OneWire oneWire(port);
  DallasTemperature sensors(&oneWire);
  sensors.begin();
  sensors.requestTemperatures();
  if (!unit) {
    return sensors.getTempCByIndex(0);
  }
  else {
    return (sensors.getTempCByIndex(0)*1.8)+32;
  }
}
