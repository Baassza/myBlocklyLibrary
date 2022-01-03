void Motor_forward(int PWMpin, int DIRpin int S) {
  pinMode(PWMpin, OUTPUT);
  pinMode(DIRpin, OUTPUT);
  int Pspeed = map(S, 0, 100, 0, 255);
  analogWrite(PWMpin, Pspeed);
  digitalWrite(DIRpin, 0);
}
void Motor_backward(int PWMpin, int DIRpin, int S) {
  pinMode(PWMpin, OUTPUT);
  pinMode(DIRpin, OUTPUT);
  int Pspeed = map(S, 0, 100, 255, 0);
  analogWrite(PWMpin, Pspeed);
  digitalWrite(DIRpin, 1);
}
void Motor_lock(int PWMpin, int DIRpin) {
  pinMode(PWMpin, OUTPUT);
  pinMode(DIRpin, OUTPUT);
  digitalWrite(PWMpin, 1);
  digitalWrite(DIRpin, 1);
}
void Motor_stop(int PWMpin, int DIRpin) {
  pinMode(PWMpin, OUTPUT);
  pinMode(DIRpin, OUTPUT);
  digitalWrite(PWMpin, 0);
  digitalWrite(DIRpin, 0);
}
