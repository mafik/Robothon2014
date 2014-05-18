#include <NewPing.h>

int LED = 13;
#define TRIGGER 12
#define ECHO 11

NewPing sonar(TRIGGER, ECHO, 200);

#define GREEN 0
#define YELLOW 1
#define RED 2

int pin[] = {3,2,1};

void setup() {
  Serial.begin(115200);
 
  for (int i = 0; i < 3; i++) {
    pinMode(pin[i],OUTPUT);
  }
}

int x(int cm) {
  if (cm == 0) return GREEN;
  if (cm > 30) return GREEN;
  if (cm > 20) return YELLOW;
  return RED;
}




void loop() {
  delay(100);
  for (int i = 0; i < 3; i++) {
    pinWrite(pin[i],LOW);
  }


  unsigned int uS = sonar.ping_cm();
  Serial.print("Ping: ");
  Serial.print(uS);
  Serial.println("cm");
  pinWrite(pin[x(uS)], HIGH);
}