#include <NewPing.h>
#include <Stepper.h>

const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
const int dirA = 12;
const int dirB = 13;

void setup() {
  Serial.begin(115200);

  //stepper setup -----------
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);

  analogWrite(pwmA, 150);
  analogWrite(pwmB, 150);
  digitalWrite(dirA, 0);
  digitalWrite(dirB, 0);

  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);

}

NewPing front(7, 6, 200);
NewPing left(5, 4, 200);

//  deadlock check ---

int lastFrontResult = -1;
int deadLockCounter = 0;

int isDeadLock(int currentFrontResult) {
  return 0;
  if (currentFrontResult > 5) {
    return 0;
  }
  //return 0;
  if (currentFrontResult >= lastFrontResult - 1 && currentFrontResult <= lastFrontResult +1) {
    if  (deadLockCounter > 100) {
      //deadLockCounter = 0;
      return 1;
    } 
    else {
      deadLockCounter++;
      return 0;
    }
  }
  else {
    deadLockCounter = 0;
    lastFrontResult = currentFrontResult;
    return 0;
  }
}

int clamp(int val, int mn, int mx) {
  if(val >= mx) return mx;
  if(val <= mn) return mn;
  return val;
}

//  end dead lock check

void loop() {
  unsigned int frontCM = front.ping_cm();
  if(frontCM == 0) frontCM = 200;
  //Serial.println(frontCM);

  if (isDeadLock(frontCM)) {
    Serial.println("deadlock found");
    analogWrite(pwmA, 200);
    analogWrite(pwmB, 200);
    digitalWrite(dirA, 1);
    digitalWrite(dirB, 1);
    do {
      delay(2000);
    } while (front.ping_cm() < 4);
      
    Serial.println("deadlock end");
  } 
  else {

    if(frontCM < 7) {
      analogWrite(pwmA, 255);
      analogWrite(pwmB, 255);
      digitalWrite(dirA, 1);
      digitalWrite(dirB, 0);
    } 
    else {
      unsigned int leftCM = left.convert_cm(left.ping_median(3));
      // if(leftCM == 0) leftCM = 200;

      //    analogWrite(pwmA, 150);
      //    analogWrite(pwmB, 150);

      analogWrite(pwmA, clamp(100 + leftCM * 20, 10, 160)); // prawy
      analogWrite(pwmB, clamp(255 - leftCM * 20, 10, 180)); // lewy

      digitalWrite(dirA, 0);
      digitalWrite(dirB, 0);
    }
  }
}


