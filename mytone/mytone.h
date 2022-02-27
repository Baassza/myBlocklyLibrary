void maketonePWM(int BUZZER, int noteFreq, int duration, int volume) {
  volume = map(volume, 0, 100, 0, 255);
  pinMode(BUZZER, OUTPUT);
  int halveWaveTime = 1 / (noteFreq * 2 );
  int waves = duration * noteFreq;
  for (int i = 0; i < waves; i++) {
    analogWrite(BUZZER, volume);
    delay(halveWaveTime * 1000);
    analogWrite(BUZZER, 0);
    delay(halveWaveTime * 1000);
  }
}

void tonerest(int duration) {
  int halveWaveTime = 1 / (294 * 2 );
  int waves = duration * 294;
  for (int i = 0; i < waves; i++) {
    delay(halveWaveTime * 1000*2);
  }
}
