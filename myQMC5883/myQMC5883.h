#include <Wire.h>
#include <MechaQMC5883.h>
MechaQMC5883 qmc;
int QMC5883Read(char Axis , uint8_t mode = Mode_Continuous, uint8_t odr = ODR_200Hz, uint8_t rng = RNG_2G, uint8_t osr = OSR_256 ) {
  uint8_t x, y, z;
  float azimuth;
  Wire.begin();
  qmc.init();
  qmc.setMode(mode, odr, rng, osr);
  qmc.read(&x, &y, &z);
  azimuth = qmc.azimuth(&y, &x);
  switch (Axis) {
    case 'A':
      return azimuth;
    case 'a':
      return azimuth;
    case 'X':
      return x;
    case 'x':
      return x;
    case 'Y':
      return y;
    case 'y':
      return y;
    case 'Z':
      return z;
    case 'z':
      return z;
    default:
    	return;
  }
}
