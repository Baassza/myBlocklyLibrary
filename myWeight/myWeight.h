#include "HX711.h"
#include <Wire.h>

#define DEC_POINT  2
#define STABLE  1

long FindZeroFactor(int DOUT, int CLK )
{
  HX711 scale(DOUT, CLK);
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average(20);
  return zero_factor;
}

float ReadWeight(int DOUT, int CLK , float offset , long calibration_factor)
{
  HX711 scale(DOUT, CLK);
  scale.set_scale(calibration_factor);
  return scale.get_units() * 0.453592;
}

long FindCalibrationFactor(int DOUT, int CLK, float real_weight ,long zero_factor)
{
  HX711 scale(DOUT, CLK);
  unsigned char state = 0;
  unsigned char flag_stable = 0;
  unsigned int decpoint = 1;
  long calibration_factor = zero_factor;
  for (unsigned char i = 0; i < DEC_POINT + 1; i++ )
    decpoint = decpoint * 10;
  while (1)
  {
    scale.set_scale(calibration_factor);
    float read_weight = scale.get_units() * 0.453592;
    long r_weight      = (real_weight * decpoint);
    long int_read_weight = read_weight * decpoint;
    long x;
    if (r_weight == int_read_weight)
    {
      flag_stable++;
      if (flag_stable >= STABLE)
      {
        return (calibration_factor);
      }
    }
    if (r_weight > int_read_weight)
    {
      x = r_weight - int_read_weight;
      if (x > 100)
        calibration_factor -= 1000;
      else if (x > 100)
        calibration_factor -= 10;
      else
        calibration_factor -= 1;
      flag_stable = 0;
    }
    if (r_weight < int_read_weight)
    {
      x =  int_read_weight - r_weight;
      if (x > 100)
        calibration_factor += 1000;
      else if (x > 10)
        calibration_factor += 10;
      else
        calibration_factor += 1;
      flag_stable = 0;
    }
  }
}


