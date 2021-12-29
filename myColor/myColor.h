#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "ColorConverterLib.h"
Adafruit_TCS34725 tcs34725 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X );
double tcs34725_capturecolor(char color)
{
  double  tcs34725_r = 0;
  double  tcs34725_g = 0;
  double  tcs34725_b = 0;
  uint16_t  tcs34725_clear = 0;
  uint16_t  tcs_red, tcs_green, tcs_blue, colorTemp, lux;
  double  tcs34725_h = 0;
  double  tcs34725_s = 0;
  double  tcs34725_v = 0;
  tcs34725.begin();
  tcs34725.setInterrupt(false);
  delay(60);
  tcs34725.getRawData(&tcs_red, &tcs_green, &tcs_blue, &tcs34725_clear);
  tcs34725.setInterrupt(true);
  if (tcs34725_clear == 0) {
    tcs34725_r = tcs34725_g = tcs34725_b = 0;
    goto re;
  }
  colorTemp = tcs34725.calculateColorTemperature_dn40(tcs_red, tcs_green, tcs_blue, tcs34725_clear);
  lux = tcs34725.calculateLux(tcs_red, tcs_green, tcs_blue);
  tcs34725_r = ((float)tcs_red / (float)(tcs34725_clear)) * 256.0;
  tcs34725_g = ((float)tcs_green / (float)(tcs34725_clear)) * 256.0;
  tcs34725_b = ((float)tcs_blue / (float)(tcs34725_clear)) * 256.0;
  ColorConverter::RgbToHsv(static_cast<uint8_t>(tcs34725_r), static_cast<uint8_t>(tcs34725_g), static_cast<uint8_t>(tcs34725_b), tcs34725_h, tcs34725_s, tcs34725_v);
  tcs34725_h = tcs34725_h * 360;
  tcs34725_s = tcs34725_s * 100;
  tcs34725_v = tcs34725_v * 100;
re:
  switch (color) {
    case 'r':
      return tcs34725_r;
    case 'R':
      return tcs34725_r;
    case 'g':
      return tcs34725_g;
    case 'G':
      return tcs34725_g;
    case 'b':
      return tcs34725_b;
    case 'B':
      return tcs34725_b;
    case 'c':
      return tcs34725_clear;
    case 'C':
      return tcs34725_clear;
    default:
      return;
  }
}
