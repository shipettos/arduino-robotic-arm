
#include <Servo.h>

const int SERVOS = 4;
const int ACC = 10; // the accurancy of the potentiometer value before idle starts counting
int PIN[SERVOS], value[SERVOS], idle[SERVOS], currentAngle[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS], previousAngle[SERVOS], ANA[SERVOS];
Servo myservo[SERVOS];

void setup()   {

  //Middle Servo
  PIN[0] = 11;          // pin to attach servo
  MIN[0] = 10;           // minimal angle of this servo based on mechanic structure
  MAX[0] = 179;         // maximum angle of this servo based on mechanic structure
  INITANGLE[0] = 90;    // initial angle at start up
  ANA[0] = 0;
  //Left Side
  PIN[1] = 10;
  MIN[1] = 10;
  MAX[1] = 115;
  INITANGLE[1] = 90;
  ANA[1] = 1;
  //Right Side
  PIN[2] = 9;
  MIN[2] = 40;
  MAX[2] = 170;
  INITANGLE[2] = 90;
  ANA[2] = 2;
  //Claw Servo
  PIN[3] = 5;
  MIN[3] = 10;
  MAX[3] = 102;
  INITANGLE[3] = 60;
  ANA[3] = 3;

  for (int i = 0; i < SERVOS; i++) {
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    value[i] = 0;
    idle[i] = 0;
    previousAngle[i] = INITANGLE[i];
  }
}

void loop() {
  for (int i = 0; i < SERVOS; i++) {
    value[i] = analogRead(ANA[i]);
    currentAngle[i] = myservo[i].read();

    if (value[i] > 800) {
      idle[i] = 0;
      if (currentAngle[i] > MIN[i]) currentAngle[i] -= 2;
      if (!myservo[i].attached()) {
        myservo[i].attach(PIN[i]);
      }
      myservo[i].write(currentAngle[i]);
    } else if (value[i] < 300) {
      idle[i] = 0;
      if (currentAngle[i] < MAX[i]) currentAngle[i] += 2;
      if (!myservo[i].attached()) {
        myservo[i].attach(PIN[i]);
      }
      myservo[i].write(currentAngle[i]);
    } else {
      ++idle[i];
    }
  }
  if (idle[3] > 100) {
    myservo[3].detach();
    idle[3] = 0;
  }

  delay(20); // Delay function to slow movement of arm down
}


