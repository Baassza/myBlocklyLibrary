#include <Ultrasonic.h>

int Getdistance(int trig, int echo) {
  Ultrasonic ultrasonic(trig, echo);
  return  ultrasonic.read();
}
