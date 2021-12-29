#include <Wire.h>
#include <math.h>
int BH1750address = 0x23;
byte buff[2];

uint16_t  BH1750Read() {
  int j = 0;
  uint16_t val = 0;
  Wire.begin();
  Wire.beginTransmission(BH1750address);
  Wire.write(0x10);
  Wire.endTransmission();
  delay(200);
  Wire.beginTransmission(BH1750address);
  Wire.requestFrom(BH1750address, 2);
  while (Wire.available())
  {
    buff[j] = Wire.read();
    j++;
  }
  Wire.endTransmission();
  if (j == 2)
  {
    return ((buff[0] << 8) | buff[1]) / 1.2;
  }
}
