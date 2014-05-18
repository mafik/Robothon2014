#include <NewPing.h>

int pins[] = {
  13, 12, 11
  
};

int idx = 0;
int N = 3;

int  lsleeptime 

void setup() {
  for(int i = 0; i < N; ++i)
    pinMode(pins[i], OUTPUT);
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
