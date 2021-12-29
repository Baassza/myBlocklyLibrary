#include <PMserial.h>


float PMSRead(PMS type, int rx, int tx, int data)
{
  SerialPM pms(type, rx, tx);
  pms.init();
  pms.read();
  float res;
  if(pms){
    switch (data) {
      case 25:
        res = pms.pm25;
        break;
      case 10:
        res = pms.pm10;
        break;
      case 1:
        res = pms.pm01;
        break;
      default:
        return;
    }
    return res;
}
}
