void setup() {
  for (int i = 8; i < 11; ++i) {
    pinMode(i, OUTPUT);
  }

}

void loop() {
  uvLed_ON(500);
  uvLed_OFF(500);
}

void uvLed_ON(int a) {
  for (int i = 8; i < 11; ++i) {
    digitalWrite(i, HIGH);
    delay(a);
  }
}

void uvLed_OFF(int a) {
  for (int i = 8; i < 11; ++i) {
    digitalWrite(i, LOW);
    delay(a);
  }
}
