#include <PCBCUPID_L293D.h>

DCMotor motor1(14);  // Motor 1
DCMotor motor2(4);  // Motor 2
DCMotor motor3(1);  // Motor 3
DCMotor motor4(2);  // Motor 4

void setup() {
  motor1.run(FORWARD);
  motor1.setSpeed(200);
  
  motor2.run(BACKWARD);
  motor2.setSpeed(150);
  
  motor3.run(FORWARD);
  motor3.setSpeed(180);
  
  motor4.run(BACKWARD);
  motor4.setSpeed(100);
}

void loop() {
  // Your control logic here
}