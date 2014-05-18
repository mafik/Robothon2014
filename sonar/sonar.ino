#include <NewPing.h>

int LED = 13;
int TRIGGER = 12;
int ECHO = 11;

int  lsleeptime 

void setup() {
  pinMode(LED, OUTPUT);
}

void all(int state) {
  for(int i = 0; i < N; ++i)
    digitalWrite(pins[i], state);
}

void on(int i) {
  digitalWrite(pins[i], 1);
}

void off(int i) {
  digitalWrite(pins[i], 0);
}

void loop() {
  off(idx);
  ++idx %= N;
  on(idx);
  delay(200);
}
