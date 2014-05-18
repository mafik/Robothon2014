#include <NewPing.h>

int LED = 13;
#define TRIGGER 12
#define ECHO 11

NewPing sonar(TRIGGER, ECHO, 200);

#define GREEN 4
#define YELLOW 2
#define RED 3

void setup() {
  Serial.begin(115200);
 
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
}

int x(int cm) {
  if (cm == 0) return GREEN;
  if (cm > 30) return GREEN;
  if (cm > 20) return YELLOW;
  return RED;
}




void loop() {
  delay(100);
  
  unsigned int uS = sonar.ping_cm();
  
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,LOW);
  digitalWrite(x(uS), HIGH);

  Serial.print("Ping: ");
  Serial.print(uS);
  Serial.println("cm");
  
}
